#!/usr/bin/env python
# -*- coding:utf-8 -*-
"""
@FileName :Tek.py
@Time :2023/6/22 8:30
@Author :shun
@describe: 常用函数，类
"""

import scipy
import numpy as np
from constant import *


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
