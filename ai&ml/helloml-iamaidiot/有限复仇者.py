# type善人=0，复仇者=1，恶人=2,行标为成员，列标1-extent，2-life，3-memory，4-type
from numpy import random
import matplotlib.pyplot as plt
from pandas import DataFrame
dic0 = {'life': [5] * 9, 'type': [0] * 9,
        'memory': [[]] * 9, 'extent': [0] * 9}
frame = DataFrame(dic0)
frame.name = '有限复仇者'
frame.index.name = '编号'
for x in range(9):
    frame.iat[x, 3] = random.randint(0, 2)
c = 0
d = 0
while d == 0:
    while c < 10:
        counter = frame['type'].value_counts()
        counter.name = c
        recorder = DataFrame(counter)
        a = random.randint(0, 8)
        b = random.randint(0, 8)
        if frame.iat[a, 3] or frame.iat[b, 3] < 0:
            break
        if a != b:
            if frame.iat[a,
                         3] + frame.iat[b,
                                        3] == 0 or frame.iat[a,
                                                             3] + frame.iat[b,
                                                                            3] == 1:
                frame.iat[a, 2] += [1]
                frame.iat[b, 2] += [1]
            if frame.iat[a, 3] + frame.iat[b, 3] == 2:
                if frame.iat[a, 2] - frame.iat[b, 2] == 0:
                    pass
                elif frame.iat[a, 2] < frame.iat[b, 2]:
                    frame.iat[a, 2] -= [2]
                    frame.iat[b, 2] += [2]
                else:
                    frame.iat[a, 2] += [2]
                    frame.iat[b, 2] -= [2]
            if frame.iat[a, 3] + frame.iat[b, 3] == 3:
                if frame.iat[a, 2] < frame.iat[b, 2]:
                    frame.iat[a, 2] -= [1]
                else:
                    frame.iat[b, 2] -= [1]
            if frame.iat[a, 3] + frame.iat[b, 3] == 4:
                frame.iat[a, 2] -= [2]
                frame.iat[b, 2] -= [2]
        cgn = frame[frame['life'] < 0]
        pgn = frame.sort_values(by='life', ascending=False)
        if len(cgn.index) == 0:
            pass
        else:
            for x, y in cgn.index, pgn.index:
                frame.iat[x, 4] = pgn.iat[y, 4]
                frame.iat[x, 2] = 10
                c += 1
                counter = frame['type'].value_counts()
                counter.name = c
                recorder[c] = counter
            if c == 10:
                d = 1
                recorder.plot()
                plt.show()
