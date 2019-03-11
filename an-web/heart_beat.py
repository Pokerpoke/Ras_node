#!/usr/bin/env python2
# -*- coding:utf-8 -*-
"""

Copyright (c) 2018 NUAA AeroLab

@file
@author   pikaqiu (2233930937@qq.com)
@date     2018-11
@brief    
@version  0.0.1

Last Modified:  2018-11-22
Modified By:    Jiang Yang (pokerpoke@qq.com)

"""
import logging,json,os
import socket, sys ,threading ,signal,time,select
import urllib,urllib2
import subprocess

# CRITICAL	50	严重错误，表明程序已不能继续运行了
# ERROR	    40	严重的问题，程序已不能执行一些功能了
# WARNING	30	有意外，将来可能发生问题，但依然可用
# INFO	    20	证明事情按预期工作
# DEBUG	    10	详细信息，调试问题时会感兴趣

# create logger with name
# if not specified, it will be root
logger = logging.getLogger('pikaqiu')
logger.setLevel(logging.DEBUG)

# create a handler, write to log.txt
# logging.FileHandler(self, filename, mode='a', encoding=None, delay=0)
# A handler class which writes formatted logging records to disk files.
fileHandler = logging.FileHandler('heartbeat.log')
fileHandler.setLevel(logging.INFO)

# create another handler, for stdout in terminal
# A handler class which writes logging records to a stream
streamHandler = logging.StreamHandler()
streamHandler.setLevel(logging.DEBUG)

# set formatter
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s :%(message)s')
fileHandler.setFormatter(formatter)
streamHandler.setFormatter(formatter)

# add handler to logger
logger.addHandler(fileHandler)
logger.addHandler(streamHandler)

class HeartBeat(object):
    def __init__(self, local_ip,local_port,buffer_size=4096,listen_number=5):
        self.local_ip=local_ip
        self.local_port=local_port
        self.buffer_size=buffer_size
        #上线节点信息列表
        self.node_list=[]
        self.request_list=[]
        #当前路径
        self.current_path=os.path.abspath(".")
        logger.debug(self.current_path)
        
        self.receiveClient=True
        self.receiveUser=True
        self.stop=True
        try:
            self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            #端口复用
            self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 
        except socket.error as e:
            logger.critical("Error creating socket: %s" %e)
            sys.exit()
        try:
            self.server.bind((self.local_ip, self.local_port))
        except socket.error as e:
            logger.critical('Error binding socket: %s' %e)
            sys.exit()
        logger.debug("Socket bind complete")
        #设置同时接收的客户端最大请求数
        self.server.listen(listen_number)
        logger.debug("Socket now listening")
    
    def get_nodeList(self):
        return self.node_list

    def receiveClientHeartBeat(self,sock,addr):
        logger.debug('Accept new connection from %s:%s...' % (addr[0],addr[1]))
        # 设置 recv 超时时间
        sock.setblocking(False)
        while self.receiveClient:
            try: 
                ready = select.select([sock], [], [], 30)
                if ready[0]:
                    data = sock.recv(self.buffer_size) 
                    tmp  = json.loads(data) 
                    #type=0为心跳包，type=1为请求视频回执包
                    #list为心跳包，dict为请求视频回执包
                    if isinstance(tmp,list):
                        self.node_list = tmp
                    else:
                        if  tmp['upload'] == True:
                            cmd = "vlc --extraintf=http:logger --verbose=2 --file-logging --logfile=vlc-log.txt"
                            cmd+=" file://%s/vlc/sdp/%s.sdp"% (self.current_path, tmp['node'])
                            cmd+=" :sout='#transcode{vcodec=theo,vb=800,acodec=vorb,ab=128,channels=2,samplerate=44100,scodec=none}"
                            cmd+=":http{dst=:%s/demo.ogg}'" % (tmp['node']+8080)
                            cmd+=" :no-sout-all :sout-keep vlc://quit"
                            subprocess.Popen(cmd,shell=True)
                            logger.debug("开始串流")
                        else :
                            logger.debug("取消")
                else:
                    self.node_list=[]
                    self.receiveClient=False
                    self.receiveUser=False
                    logger.debug('Connection from %s:%s timeout.' % addr)
                    break
                # logger.debug(node_list)
            except socket.error as e:
                self.receiveClient=False
                self.receiveUser=False
                logger.critical("current  %s:%s tcp connection error %s" % (addr[0],addr[1],e))
                break
        sock.close()
        logger.debug('heartbeat Connection from %s:%s closed.' % addr)

    #向节点num请求视频
    def selectNode(self,num,call):
        #call true为请求网络视频 false为停止接收
        d = dict(node=num, port=8000+num*2, request=call)
        d_string=json.dumps(d)
        return d_string

    def receiveUserCommand(self,sock,addr):
        logger.debug('ready to request video from %s:%s...' % (addr[0],addr[1]))
        while self.receiveUser:
            try:
                #把已上线的节点传给网页服务器
                url = 'http://127.0.0.1:5000/nodelist'
                headers = {'Content-Type': 'application/json'}
                req=urllib2.Request(url,data=json.dumps(self.node_list),headers=headers)
                response = urllib2.urlopen(req)
                request_msg=response.read().decode('utf-8')
                if request_msg == 'ok':
                    pass
                    # logger.debug('Data:%s'% request_msg)# 获取服务器返回的页面信息 
                else :
                    #寻找节点上传视频
                    request = json.loads(request_msg)
                    self.node_request=self.selectNode(request['node'],True)
                    sock.send((self.node_request.decode('utf-8')).encode('utf-8'))
            except socket.error as e:
                logger.critical("current  %s:%s tcp connection error %s" % (addr[0],addr[1],e))
                break
            except urllib2.URLError as e:
                self.receiveClient=False
                self.receiveUser=False  
                logger.debug('current page return error %s'% e.reason)
                break
            time.sleep(1)
        sock.close()
        logger.debug('command Connection from %s:%s closed.' % addr)

    #退出线程中断处理函数
    def quit(self, signum, frame):
        # logger.debug("Got signal: %s" % signum)
        pass

    def stopHeartBeat(self):
        self.receiveClient=False
        self.receiveUser=False
        self.stop=False

    def start(self):
        while self.stop:
            try:
                sock, addr = self.server.accept()
                logger.debug(addr)
                self.receiveClient=True
                self.receiveUser=True
                t1 = threading.Thread(target=self.receiveClientHeartBeat, args=(sock, addr))
                t2 = threading.Thread(target=self.receiveUserCommand, args=(sock, addr))
                t1.setDaemon(True)
                t2.setDaemon(True)
                t1.start()
                t2.start()
            except KeyboardInterrupt :
                self.receiveClient=False
                self.receiveUser=False
                self.stop=False
                logger.error("Program interrupted by user.")
                break
        self.server.close()
        logger.debug('server had stopped work')
if __name__ == '__main__':
    heartbeat=HeartBeat("0.0.0.0",6000)
    heartbeat.start()