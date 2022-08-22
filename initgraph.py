import re
import os
from os import path
if __name__ == "__main__":
    prob_name = "crd103"
    file_name = path.dirname(__file__) + "/CRD/" + prob_name
    inp = open(file_name, 'r', encoding='utf-8')
    for line in inp.readlines():
        seg_list = re.sub('\t|\n| ', '\n', line)  # 批量将tab，换行符，空格替换为空串
        neoseg_list = re.sub(' ', '\n', line)
        # 写入输出文件
        output = open('olddata.txt', 'a', encoding='utf-8')  # a为在后边接着写入的模式。w为删除原来的在写入的模式
        output.write(neoseg_list)
    output.close()
    inp.close()
    with open('olddata.txt', 'r', encoding='utf-8') as fr, open(prob_name+'.txt', 'w', encoding='utf-8') as fd:
        for text in fr.readlines():
            if text.split():
                fd.write(text)
    os.remove('olddata.txt')
