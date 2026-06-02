##########################
###    COMMAND FILE    ###
##########################

import re
import sys
import csv
import signalsGetter

CSV_FIELDS = ['module', 'signal', 'lenght', 'type']
CSV_FILENAME = 'allSignals.csv'

# mode: file reading mode (w, r, a, etc.).
# rowtype: d for dictionary, l to list.
# fields: always a list
# rows: can be dictionary or list
def write_csv(file, fields, rows, mode='w', rowtype='d'):
    with open(file, mode) as f:
        if rowtype == 'l':
            writer = csv.writer(f)  
            if mode=='w': writer.writerow(fields)
        elif rowtype == 'd':  
            writer = csv.DictWriter(f, fieldnames=fields)  
            writer.writeheader()  

        writer.writerows(rows)
    f.close()

# rowtype: d for read as dictionary, l to read as list.
def read_csv(file, rowtype='d'):
    read_signals=[]
    with open(file, 'r') as f:
        if rowtype == 'l':
            reader = csv.reader(f)
        elif rowtype == 'd':
            reader = csv.DictReader(f)
            
        for i in reader: read_signals.append(i)
    f.close()

    return read_signals





# Function called when request previous detected signals,
# it runs reading of csv file (recomended when project is large).
def get_signals_from_csv(file, pretty_info=True):
    retSignals = []
    try:
        signals = read_csv(file=f'.{CSV_FILENAME}', rowtype='d')
    except FileNotFoundError:
        print('If it is the first time of your proyect, please use the -r option')
        exit(0)

    module_name = file.split("/")[-1].split(".")[0][1:]
    signals = list(filter(lambda item: item['module'] == module_name, signals))

    for signal in signals:
        s = signalsGetter.Signal()
        s.name = signal['signal']
        s.type = signal['type']
        s.size = signal['lenght']
        retSignals.append(s)

        # plural='s'
        # if int(signal['lenght']) == 1:
        #     plural=' '
        # if pretty_info:
        #     print( '{}, {} bit{}: {}'.format(signal['type'], signal['lenght'], plural, signal['signal']) )
        # else:
        #     print( '{},{},{}'.format(signal['type'], signal['lenght'], signal['signal']) )
    return retSignals



# Function called when request refreshing (-r) detected signals,
# it runs verilator compilation to obtain them.
def get_signals_from_compilation(file, csvwritemode):
    wfile = open(file, 'r')
    module_name = file.split("/")[-1].split(".")[0][1:]

    signals=[]
    save_line=False
    csv_rows=[]

    # Get all signals detected 
    for line in wfile.readlines():
        if '// PORTS' in line:
            save_line = True

        # Signals IN and OUT are between PORTS and CELLS lines into .h file.
        if save_line and '//' not in line:
            added_line = line.replace('\t', ' ').replace(r'\s+', ' ').strip()
            if added_line != '':
                signals.append(added_line)

        if '// CELLS' in line:
            save_line = False
            break


    # Process dignals names and lengths
    for signal in signals:
        csv_row=[]

        if 'VL_IN' in signal:
            signal_type = 'INPUT'

        elif 'VL_OUT' in signal:
            signal_type = 'OUTPUT'


        parts=signal.split(',')

        signal_name = parts[0][parts[0].find('&')+1:]
        signal_lenght = int(parts[1]) + 1

        # Order in csv_row must be strict, because of .csv organization
        csv_row.append(module_name)
        csv_row.append(signal_name)
        csv_row.append(signal_lenght)
        csv_row.append(signal_type)

        csv_rows.append(csv_row)

    wfile.close()

    # Write the csv asking one last time if csv already exists in order to avoid overwriting
    write_csv(file=f'.{CSV_FILENAME}', fields=CSV_FIELDS, rows=csv_rows, rowtype='l', mode=csvwritemode)


def get_signals(v_file, write_option, option='n'):
    s1 = signalsGetter.Signal()
    s1.name = "signal1"
    s1.type = "INPUT"
    s1.size = 10

    s2 = signalsGetter.Signal()
    s2.name = "signal2"
    s2.type = "OUTPUT"
    s2.size = 20

    # Refresh option
    if option == 'r':
        get_signals_from_compilation(v_file, write_option)
        #return [s1, s2]
    # Intern usage option
    elif option == 'i':
        return [s1, s2]
        #get_signals_from_csv(file=v_file, pretty_info=False)
    # Default: print option
    else:
        return get_signals_from_csv(file=v_file)

if __name__ == '__main__':
    # Ask again ('cause first ask is on .sh) in order to select the function
    option = str(sys.argv[1])
    v_file = str(sys.argv[2])
    
    # Refresh option
    if option == 'r':
        write_option = str(sys.argv[3])
        get_signals_from_compilation(v_file, write_option)
    # Intern usage option
    elif option == 'i':
        get_signals_from_csv(file=v_file, pretty_info=False)
    # Default: print option
    else:
        get_signals_from_csv(file=v_file)

    








