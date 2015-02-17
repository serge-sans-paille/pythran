#!/usr/bin/env python
from pythran import tables

TITLE = "Supported Modules and Functions"

DEPTHS = '=*-+:~#.^"`'

print(DEPTHS[0]*len(TITLE))
print(TITLE)
print(DEPTHS[0]*len(TITLE))
print("")


def format_name(name):
    if name.endswith('_') and not name.startswith('_'):
        name = name[:-1]
    return name


def isiterable(obj):
    return hasattr(obj, '__iter__')


def dump_entry(entry_name, entry_value, depth):
    if isiterable(entry_value):
        print(entry_name)
        print(DEPTHS[depth] * len(entry_name))
        print("")
        sym_entries, sub_entries = [], []
        for sym in entry_value:
            w = sub_entries if isiterable(entry_value[sym]) else sym_entries
            w.append(sym)
        for k in sorted(sym_entries):
            dump_entry(format_name(k), entry_value[k], depth + 1)
        print("")
        for k in sorted(sub_entries):
            dump_entry(format_name(k), entry_value[k], depth + 1)
            print("")
    else:
        print(entry_name)


for MODULE in sorted(tables.MODULES):
    if MODULE != '__dispatch__':
        dump_entry(format_name(MODULE), tables.MODULES[MODULE], 1)
