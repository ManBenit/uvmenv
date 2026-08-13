#########################
###    CONFIG FILE    ###
#########################

# ====================
# Python imports
# ====================
import csv
import sys
import os
import cocotb


def __read_csv(file, rowtype='d'):
    read_signals=[]
    with open(file, 'r') as f:
        if rowtype == 'l':
            reader = csv.reader(f)
        elif rowtype == 'd':
            reader = csv.DictReader(f)
            
        for i in reader: read_signals.append(i)
    f.close()

    return read_signals

def get_dut_signames(module: str = str(cocotb.top), type: str = None, length: int = None):
    hdl_src = next( p for p in sys.path if p.endswith('HDLSrc') )
    retSignals = []
    signals = __read_csv(file=os.path.join(hdl_src, '.allSignals.csv'), rowtype='d')

    # Dynamic filters
    if module != 'all':
        signals = list(filter(lambda item: item['module'] == module, signals))
    if type:
        signals = list(filter(lambda item: item['type'] == type, signals))
    if length:
        signals = list(filter(lambda item: item['length'] == str(length), signals))

    # Add results to list
    for signal in signals:
        retSignals.append( signal['signal'] )

    return retSignals
