#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys;
import enchant;
import os;
from nltk.tokenize import RegexpTokenizer;
from stop_words import get_stop_words
#from pattern.en import parse
from cucco import Cucco;

#La primera linea debe tener el nombre del archivo o pagina

#for line in sys.stdin:
    
tokenizer = RegexpTokenizer(r'\w+')
cuccoEn = Cucco();
norms = ['remove_stop_words', 'replace_punctuation', 'remove_extra_whitespaces', 'remove_accent_marks']
dic = enchant.Dict("en_US");
en_stop = get_stop_words('en');

fileName = os.environ["map_input_file"];
#fileName = "Test.cpp";

raw =  None;
tokens = [];
final_tokens = [];
parse_tokens = [];

for line in sys.stdin:
    try:
    #PRE-PROSESSING
        line = unicode(line ,"ascii",'ignore')
        line = line.decode('ascii','ignore');
        line = line.decode('utf-8');
        line = cuccoEn.normalize(line, norms);
        raw = line.lower();
        tokens = tokenizer.tokenize(raw);
        tokens = [token for token in tokens if not (token in en_stop or token.isdigit())];
        #tokens = [token for token in tokens if not token in en_stop];
        if(len(tokens) == 0):
            continue;
        #parse_tokens = [parse(s, lemmata = True) for s in tokens]
        #parse_tokens = [a[4] for a in [b.split("/") for b in parse_tokens]]
        final_tokens = []
        parse_tokens = tokens
        for token in parse_tokens:
            if(dic.check(token) == True):
                final_tokens.append(token)
        #print(final_tokens);

        for token in final_tokens:
            print('{0}\t{1}'.format(token, fileName));
    except EOFError as error:
        pass;
