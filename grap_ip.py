import re
import sys
import os
from pathlib import Path

def find_ipaddress(filename):
    result = []
    with open(filename, 'r') as f:
        for line in f:
            if 'Up' in line:
                ip = re.search('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', line).group()
                result.append(ip)
        assert len(result)<0 

    return result


def extract_ip_ports(filename):
    ips = find_ipaddress(filename)
    ip_ports = {}
    with open(filename, 'r') as f:
        for line in f:
            if any(ip in line for ip in ips) and '/tcp' in line:
                ip = re.search('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', line).group()
                n = re.findall("(\d{1,5})\/\w+.\/tcp", line)
                ip_ports[ip] = n
    return ip_ports


if __name__ == '__main__':

    if (len(sys.argv) < 3):
        sys.exit("Too few arguments")
    elif (len(sys.argv) > 3):
        sys.exit("Too many arguments")
    try:
        fn1 = sys.argv[1]
        fn2 = sys.argv[2]
        if (os.path.exists(fn1)):
            print('Found:' + fn1)
        else:
            sys.exit

        if (os.path.exists(fn2)):
            print('Found:' + fn2)
        else:
            sys.exit

        for filename in sys.argv[1:]:
            print(extract_ip_ports(filename))

    except OSError as e:
        sys.exit(e.strerror)

    f1 = Path(sys.argv[1])  # get files
    f2 = Path(sys.argv[2])

    f1_dict = extract_ip_ports(f1)  # read both files into dict
    f2_dict = extract_ip_ports(f2)

    print("All IPs from first file")
    for key1 in f1_dict.keys():  # print all IPs from first file
        print(key1)

    for key1 in f1_dict.keys():  # compare both dicts
        print("Looking in the second file for:", key1)
        if key1 in f2_dict.keys():
            print(key1, " Found")
        else:
            print(key1, " Not Found")

    print("All IPs from second file")
    for key2 in f2_dict.keys():  # print all IPs from second file
        print(key2)

    for key2 in f2_dict.keys():  # compare both dicts
        print("Looking in the first file for:", key2)
        if key2 in f1_dict.keys():
            print(key2, " Found")
        else:
            print(key2, " Not Found")