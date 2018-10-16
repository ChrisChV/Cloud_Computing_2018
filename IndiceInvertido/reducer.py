#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys;

key = None;
fileName = None;

mapper = {};

for line in sys.stdin:
    try:
        line = unicode(line ,"ascii",'ignore')
        line = line.decode('ascii','ignore');
        line = line.decode('utf-8');
        line = line.strip();

        key, fileName = line.split("\t");

        if key in mapper:
            if not fileName in mapper[key]:
                mapper[key].append(fileName);
        else:
            mapper[key] = [];
            mapper[key].append(fileName);
    except EOFError as error:
        pass;
    
tempString = None;

for key, files in mapper.iteritems():
    tempString = key + "\t";
    for name in files:
        tempString += name + " ";
    print(tempString);