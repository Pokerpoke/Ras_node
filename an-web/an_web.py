#!/usr/bin/env python3
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
from flask import Flask, request, render_template, send_from_directory, Response
import logging
import json
from queue import Queue

# init logger
logger = logging.getLogger('an_web')
logger.setLevel(logging.DEBUG)

# set stream handle
# file
fileHandler = logging.FileHandler('an_web.log')
fileHandler.setLevel(logging.INFO)
# standard output
streamHandler = logging.StreamHandler()
streamHandler.setLevel(logging.DEBUG)

# set format
formatter = logging.Formatter(
    '%(asctime)s - %(name)s - %(levelname)s :%(message)s')
fileHandler.setFormatter(formatter)
streamHandler.setFormatter(formatter)

# add handler to logger
logger.addHandler(fileHandler)
logger.addHandler(streamHandler)

# flask
app = Flask(__name__)

current_user_command = 0
current_node_list = []


@app.route('/')
def index():
    return render_template('./templates/index.html')


@app.route('/icon/favicon.ico', methods=['GET', 'POST'])
def get_icon():
    return Response(file("./icon/favicon.ico"), direct_passthrough=True)


@app.route('/<filename>', methods=['GET', 'POST'])
def get_file(filename):
    # return send_from_directory("./videos",filename)
    return Response(file("./videos/" + filename), direct_passthrough=True)


@app.route('/nodelist', methods=['GET'])
def ret_nodelist():
    global current_node_list
    return json.dumps(current_node_list).encode('utf-8')


@app.route('/nodelist', methods=['POST'])
def get_nodelist():
    global current_user_command
    global current_node_list
    current_node_list = request.get_json()
    logger.debug(current_node_list)
    if current_node_list and current_user_command > 0:
        for node in current_node_list:
            if node['node'] == current_user_command:
                current_user_command = 0
                return json.dumps(node)
    return 'ok'.encode('utf-8')


@app.route('/request/<int:post_id>', methods=['GET'])
def video(post_id):
    global current_user_command
    global current_node_list
    logger.debug("current request id is %s" % post_id)
    if current_node_list and post_id > 0:
        for node in current_node_list:
            if node['node'] == post_id:
                if node['upload'] == False:
                    current_user_command = post_id
                return 'ok'.encode('utf-8')
    return 'fail'.encode('utf-8')


def start():
    app.run('0.0.0.0', 5000)


if __name__ == '__main__':
    start()
