'''
This Python file will help you download/clip the template.
Check out the link below to see what template you can use.
link: https://github.com/revival0728/CP-Template
All the files in this repository can be download.
But the files in the 'clipraw' just only for copping.

Notice: this file reuires module 'getopt' and 'clipboard'
'''

help_text = '''
'-n' and '--name' is for picking up which template your want
'-d' and '--download' means download the template   # need argument < file name >
'-c' and '--clip' means set your clipboard to the template   # clip from /clipraw/
'''

import urllib.request
import getopt
import sys
import clipboard

pre_url = 'https://raw.githubusercontent.com/revival0728/CP-Template/master/'
short_cmd = 'hcd:n:'
long_cmd = ['help', 'clip', 'download=', 'name=']

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
                f.write(file.decode('utf8'))
                f.close()
        else:
            url = pre_url + '/clipraw/' + name + '.cpp'
            file = urllib.request.urlopen(url).read()
            clipboard.copy(file.decode('utf8'))
            print('{} had clipped in clipboard'.format(name))
    except urllib.request.urlopenError:
        print('Template not found')
        return

if __name__ == '__main__':
    main()