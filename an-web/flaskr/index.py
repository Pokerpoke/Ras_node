#!/usr/bin/env python3
# -*- coding:utf-8 -*-
"""

Copyright (c) 2018 NUAA AeroLab

@file
@author   Jiang Yang (pokerpoke@qq.com)
@date     2018-11
@brief    
@version  0.0.1

Last Modified:  2018-11-23
Modified By:    Jiang Yang (pokerpoke@qq.com)

"""
from flask import (
    Blueprint, render_template, request
)
import json

bp = Blueprint('index', __name__, url_prefix='/')

user_command = 0
node_list = []


@bp.route('/')
def index():
    return render_template('index.html')


@bp.route('/nodelist', methods=['GET'])
def get_nodelist():
    global node_list
    return json.dumps(node_list).encode('utf-8')


@bp.route('/nodelist', methods=['POST'])
def post_nodelist():
    global node_list
    global user_command
    node_list = request.get_json()
    if node_list and user_command > 0:
        for node in node_list:
            if node['node'] == user_command:
                user_command = 0
                return json.dumps(node)
    return 'ok'.encode('utf-8')


@bp.route('/request/<int:post_id>', methods=['GET'])
def video(post_id):
    global user_command
    global node_list
    if node_list and post_id > 0:
        for node in node_list:
            if node['node'] == post_id:
                if node['upload'] == False:
                    user_command = post_id
                return 'ok'.encode('utf-8')
    return 'fail'.encode('utf-8')
