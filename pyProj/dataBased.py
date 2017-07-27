# coding=utf-8

import matplotlib
matplotlib.use('Agg')

from matplotlib.ticker import MultipleLocator, FormatStrFormatter

import matplotlib.pyplot as plt
import matplotlib.font_manager as font_mgr
import numpy as np

chf = font_mgr.FontProperties(fname='MSYH.TTC')

#将x主刻度标签设置为20的倍数
# xmajorLocator   = MultipleLocator(50)
#设置x轴标签文本的格式
# xmajorFormatter = FormatStrFormatter('%1.1f') 
#将x轴次刻度标签设置为5的倍数
xminorLocator   = MultipleLocator(100)

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


labels = (u'蚂蚁小宝卡', u'蚂蚁红包卡(电信)', u'蚂蚁小宝+卡')
# a.extend(b)

# x0 = np.linspace(0, voiceTimeMax, voiceTimeMax)

# prepare
# 小宝卡 联通
basedData = 200
a0 = np.linspace(0, basedData, 2) # 线下支付兑换
b0 = [6, 6] #+ 0 * a0
# 1g计算
a1 = np.linspace(basedData, basedData+200, 200)
b1 = b0[-1] + 0.1 * (a1 - basedData)
a2 = np.linspace(basedData+200, basedData+1024, 2) # 价格不变
b2 = [max(b1), max(b1)] #+ 0 * a2
# 类推下1G
basedData += 1024
a3 = np.linspace(basedData, basedData+200, 200)
b3 = b2[-1] + 0.1 * (a3 - basedData)
a4 = np.linspace(basedData+200, basedData+1024, 2)
b4 = [max(b3), max(b3)] # + 0 * a2

# 蚂蚁红包卡(电信)
basedData = 300
c0 = np.linspace(0, basedData, 2) # 套餐内
d0  = [9, 9] # + 0.075 * x0
# 1g计算
c1 = np.linspace(basedData, basedData+150, 150)
d1 = d0[-1] + 0.05 * (c1 - basedData)
c2 = np.linspace(basedData+150, basedData+1024, 2) # 价格不变
d2 = [max(d1), max(d1)] #+ 0 * a2
# 类推下1G
basedData += 1024
c3 = np.linspace(basedData, basedData+200, 200)
d3 = d2[-1] + 0.05 * (c3 - basedData)
c4 = np.linspace(basedData+200, basedData+1024, 2)
d4 = [max(d3), max(d3)] # + 0 * a2

# 蚂蚁小宝+卡
basedData = 200+1024
e0 = np.linspace(0, basedData, 2) # 线下支付兑换
f0 = [16, 16] #+ 0 * a0

# 类推下1G
e1 = np.linspace(basedData, basedData+150, 150)
f1 = f0[-1] + 0.1 * (e1 - basedData)
e2 = np.linspace(basedData+150, basedData+1024, 2)
f2 = [max(f1), max(f1)] # + 0 * a2

# support line
# sup_x_0 = (120, 120)
# sup_y_0 = np.linspace(0, 18, 2)

# sup_x_1 = (200, 200)
# sup_y_1 = np.linspace(0, 9+0.075*200, 2)

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

# 小宝卡
ax.plot(a0, b0, 'k--')
ax.plot(a1, b1, 'k--')
ax.plot(a2, b2, 'k--')
ax.plot(a3, b3, 'k--')
ax.plot(a4, b4, 'k--', label = labels[0])
# 红包卡
ax.plot(c0, d0, 'k')
ax.plot(c1, d1, 'k')
ax.plot(c2, d2, 'k')
ax.plot(c3, d3, 'k')
ax.plot(c4, d4, 'k', label = labels[1])
# 小宝+
ax.plot(e0, f0, 'k:')
ax.plot(e1, f1, 'k:')
ax.plot(e2, f2, 'k:', label = labels[2])

# ax.plot(sup_x_0, sup_y_0, 'k:')
# ax.plot(sup_x_1, sup_y_1, 'k:')
# ax.text(0.5, 0.5,'matplotlib', horizontalalignment='center',
	# verticalalignment='center', transform=ax.transAxes)

# plt.plot(x1, y1, color="red")
# L1, = plt.plot(x2, y2, label = 'Line 1', color="red")
# plt.plot(x0, y3, color="red")
# L2, = plt.plot(x0, z, label = 'Line 2', color="blue")


# plt.xlabel("Time(s)")
# plt.legend()
ax.set_xlabel(u'流量 / MB', fontproperties=chf)
ax.set_ylabel(u'费用 / 元', fontproperties=chf)
ax.set_title(u'费用对比', fontproperties=chf)

# plt.xlabel(u'通话时间 / 分钟', fontproperties=chf)
# plt.ylabel(u'费用 / 元', fontproperties=chf)
# plt.title(u'移动 电信 费用对比', fontproperties=chf)

legend = ax.legend(loc='upper center', shadow=True, fontsize='x-large', prop=chf)
legend.get_frame().set_facecolor('#00FFCC')

# plt.legend((L1, L2), (u'移动本地A', u'蚂蚁红包卡(电信)'), prop=chf)

plt.savefig("DataCompared.png", dpi=600)