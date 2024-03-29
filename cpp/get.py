'''
This Python file will help you download/clip the template.
Check out the link below to see what template you can use.
link: https://github.com/revival0728/CP-Template
All the files in this repository can be download.
But the files in the 'clipraw' just only for copping.

Notice: this file reuires module 'getopt' and 'clipboard'
        you can use 'py get.py --setup' to setup the envirment
'''

help_text = '''
'-n' and '--name' is for picking up which template your want
'-d' and '--download' means download the template   # need argument < file name >
'-c' and '--clip' means set your clipboard to the template   # clip from /clipraw/
'--setup' is the command for setting up the envirment
'''

import urllib.request
import getopt
import sys
import os
import clipboard

pre_url = 'https://raw.githubusercontent.com/revival0728/CP-Template/master/cpp'
short_cmd = 'hcd:n:'
long_cmd = ['help', 'clip', 'download=', 'name=', 'setup']

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], short_cmd, long_cmd)

        if opts == []:
            print('command not found')
            return
        fname = ''
        name = ''
        dop = None
        for k, v in opts:
            if k in ('-d', '--download'):
                dop = True
                fname = v
            elif k in ('-c', '--clip'):
                dop = False
            elif k in ('-n', '--name'):
                name = v
            elif k in ('-h', '--help'):
                print(help_text)
                return
            elif k in ('--setup'):
                os.system('python -m ensurepip')
                os.system('python -m pip install --upgrade pip')
                os.system('pip install clipboard')
                return
    except getopt.GetoptError:
        print('Wrong Arguments')
        return
    if not '.cpp' in fname:
        fname += '.cpp'
    try:
        if dop:
            url = pre_url + name + '.cpp'
            file = urllib.request.urlopen(url).read()
            print('Downloading {} to {}'.format(name, fname))
            with open(fname, 'w') as f:
                f.write(file.decode('utf8').replace('\r', ''))
                f.close()
        else:
            url = pre_url + '/clipraw/' + name + '.cpp'
            file = urllib.request.urlopen(url).read()
            clipboard.copy(file.decode('utf8').replace('\r', ''))
            print('{} had clipped in clipboard'.format(name))
    except urllib:
        print('Template not found')
        return

if __name__ == '__main__':
    main()
