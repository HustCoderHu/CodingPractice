# coding=utf-8

import matplotlib
matplotlib.use('Agg')

from matplotlib.ticker import MultipleLocator, FormatStrFormatter

import matplotlib.pyplot as plt
import matplotlib.font_manager as font_mgr
import numpy as np

chf = font_mgr.FontProperties(fname='MSYH.TTC')

voiceTimeMin = 0
voiceInPackage = 150
voiceTimeMax = 250

#将x主刻度标签设置为20的倍数
# xmajorLocator   = MultipleLocator(50)
#设置x轴标签文本的格式
# xmajorFormatter = FormatStrFormatter('%1.1f') 
#将x轴次刻度标签设置为5的倍数
xminorLocator   = MultipleLocator(10)

#将y轴主刻度标签设置为 的倍数
ymajorLocator   = MultipleLocator(2)
#设置y轴标签文本的格式
# ymajorFormatter = FormatStrFormatter('%1.1f')
#将此y轴次刻度标签设置为 的倍数
# yminorLocator   = MultipleLocator(0.1)

#将y轴主刻度标签设置为0.5的倍数
# ymajorLocator   = MultipleLocator(0.5)
#将y次刻度标签设置为2的倍数
# yminorLocator   = MultipleLocator(2)


labels = (u'移动本地A', u'蚂蚁红包卡(电信)', u'蚂蚁小宝卡(联通)')
# a.extend(b)

x0 = np.linspace(0, voiceTimeMax, voiceTimeMax)

# prepare
# 移动本地A
x1 = np.linspace(0, voiceInPackage, 2)
a0 = [18, 18] #+ 0 * x1
x2 = np.linspace(voiceInPackage, voiceTimeMax,
				voiceTimeMax - voiceInPackage)
a1 = 18 + 0.12 * (x2 - voiceInPackage)
# y3 = 18 + 0.12 * (max(x0, voiceInPackage) - voiceInPackage)

# 蚂蚁红包卡(电信)
# x0 = np.linspace(0, voiceTimeMax, voiceTimeMax)
b  = 9 + 0.075 * x0

# 蚂蚁小宝卡
c = 6 + 0.15 * x0


# support line
sup_x_0 = (120, 120)
sup_y_0 = np.linspace(0, 18, 2)

sup_x_1 = (200, 200)
sup_y_1 = np.linspace(0, 9+0.075*200, 2)

# draw graph
fig, ax = plt.subplots()

#设置主刻度标签的位置,标签文本的格式
# ax.xaxis.set_major_locator(xmajorLocator)
# ax.xaxis.set_major_formatter(xmajorFormatter)
ax.yaxis.set_major_locator(ymajorLocator)
# ax.yaxis.set_major_formatter(ymajorFormatter)

#显示次刻度标签的位置,没有标签文本
ax.xaxis.set_minor_locator(xminorLocator)
# ax.yaxis.set_minor_locator(yminorLocator)
# ax.yaxis.set_major_locator(ymajorLocator)

ax.plot(x1, a0, 'k--')
ax.plot(x2, a1, 'k--', label = labels[0])
ax.plot(x0, b, 'm', label = labels[1])
ax.plot(x0, c, 'k:', label = labels[2])

ax.plot(sup_x_0, sup_y_0, 'k:')
ax.plot(sup_x_1, sup_y_1, 'k:')
# ax.text(0.5, 0.5,'matplotlib', horizontalalignment='center',
	# verticalalignment='center', transform=ax.transAxes)

# plt.plot(x1, y1, color="red")
# L1, = plt.plot(x2, y2, label = 'Line 1', color="red")
# plt.plot(x0, y3, color="red")
# L2, = plt.plot(x0, z, label = 'Line 2', color="blue")


# plt.xlabel("Time(s)")
# plt.legend()
ax.set_xlabel(u'通话时间 / 分钟', fontproperties=chf)
ax.set_ylabel(u'费用 / 元', fontproperties=chf)
ax.set_title(u'费用对比', fontproperties=chf)

# plt.xlabel(u'通话时间 / 分钟', fontproperties=chf)
# plt.ylabel(u'费用 / 元', fontproperties=chf)
# plt.title(u'移动 电信 费用对比', fontproperties=chf)

legend = ax.legend(loc='upper center', shadow=True, fontsize='x-large', prop=chf)
legend.get_frame().set_facecolor('#00FFCC')

# plt.legend((L1, L2), (u'移动本地A', u'蚂蚁红包卡(电信)'), prop=chf)

plt.savefig("yidong_dianxin.png", dpi=600)