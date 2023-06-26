#!/usr/bin/env python
# -*- coding:utf-8 -*-
"""
@FileName :Tek.py
@Time :2023/6/22 8:30
@Author :shun
@describe: TODO
"""

import sys
import scipy
import numpy as np
from constant import *


class Tek(object):
    """
    Tek 示波器文件类
    """

    def __init__(self, filename) -> int:
        self.filename = filename
        self.parameters = self.read_parameters()
        self.t, self.s = self.read_data()
        self.frequency = 1 / self.parameters['Sample Interval'].astype(
            np.float64)

    def read_parameters(self) -> dict:
        """
        读取 tex 文件设置

        :return dict: 参数和值对应的字典
        """
        try:
            data = np.loadtxt(self.filename,
                              dtype="str",
                              delimiter=",",
                              usecols=(0, 1),
                              unpack=True)
            temp = {
                key: value
                for key, value in zip(data[0][:18], data[1][:18]) if key != ''
            }
            return temp
        except Exception as e:
            print(e)

    def read_data(self) -> tuple:
        """
        读取 tex 文件数据

        :return tuple: 返回第3、4列，两个列表，需要两个变量接收
        """
        try:
            data = np.loadtxt(self.filename,
                              delimiter=",",
                              usecols=(3, 4),
                              unpack=True)
            return (data[0], data[1])
        except Exception as e:
            print(e)


class Radar(object):
    """
    雷达类
    """

    def __init__(self, B, T) -> None:
        # 调制带宽
        self.B = B
        # 调制周期
        self.T = T
        # 波长
        self.lambda_ = 1064
        # 基础频率
        self.fc = c / self.lambda_

    def cal_B(self, d: float, f_if: float) -> float:
        """
        根据距离和中频计算带宽

        :param float d: 距离
        :param float f_if: 中频频率
        :return float: 带宽
        """
        d = 2
        f_if = 65000
        return (f_if * c * self.T) / (2 * d)

    def cal_d(self, f_if: float) -> float:
        """
        计算距离

        :param float f_if: 中频
        :return float: 距离
        """
        return (f_if * c * self.T) / (2 * self.B)

    def cal_d(self, f1: float, f2: float) -> float:
        """
        计算速度

        :param float f1: 上扫
        :param float f2: 下扫
        :return float: 速度
        """
        return (c * ((f1 - f2))) / (4 * self.fc)


def find_heighest_peak(sequence: list) -> tuple:
    """
    寻找最大峰值索引和最大峰值

    :param list sequence: 待求序列
    :return tuple: 返回最大峰值索引和最大峰值
    """
    # 寻找峰值
    pks, locs = scipy.signal.find_peaks(sequence, height=0)
    # 最大峰值在峰值列表 pks_up 中的索引
    max_index_pks = np.argmax(locs['peak_heights'])
    # 最大峰值
    max_value = np.amax(locs['peak_heights'])
    # 最大值在序列中的索引
    max_index = pks[max_index_pks]
    # 返回最大峰值索引和最大峰值
    return (max_index, max_value)


if __name__ == "__main__":
    a = [1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 6, 5, 4, 3, 2]
    v = find_heighest_peak(a)
    print(v)

    radar = Radar()
    a = radar.cal_d(2, 65000)
    pass
