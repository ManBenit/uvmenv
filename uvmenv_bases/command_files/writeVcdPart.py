import sys



def remove_lines(filepath, start, end):
    # Ensure a valid range
    if start > end:
        start, end = end, start
    
    with open(filepath, 'r') as file:
        lines = file.readlines()
    
    # Filter lines ut of specified range
    remaining_lines = [
        line for i, line in enumerate(lines, start=1) if i < start or i > end
    ]
    
    # Rewrite lines
    with open(filepath, 'w') as file:
        file.writelines(remaining_lines)


def get_index_of_line(filepath, text):
    top = open(filepath, 'r')
    
    top_lines = top.readlines()

    for index, line in enumerate(top_lines):
        if text in line.strip(): 
            return index+1

    top.close()


def count_lines(filepath):
    with open(filepath, 'r') as file:
        total_lines = sum(1 for _ in file)
    return total_lines


def append_unique_to_file(filepath, text):
    with open(filepath, 'r+') as file:
        content = file.read()
        if '//vcd_dump' not in content or text=='endmodule\n':
            file.write(text)
        #    print("Texto único agregado exitosamente.")
        #else:
        #    print("El texto ya está presente en el archivo.")



if __name__=='__main__':
    topfile = str(sys.argv[1])
    topmodule = topfile.split('.')[0]
    topmodule = topmodule.split('/')[-1]
    level = int(sys.argv[2])
    option = int(sys.argv[3])
    
    # Delete last line (endmodule)
    if option == 1:
        init_line = get_index_of_line(topfile, 'endmodule')
        end_line = count_lines(topfile)

        remove_lines(topfile, init_line, end_line)

    # Write new lines    
    elif option == 2:
        new_string=f'//vcd_dump\ninitial begin $dumpfile("dut_signals.vcd");$dumpvars({level}, {topmodule}); end\n'
        append_unique_to_file(topfile, new_string)
        append_unique_to_file(topfile, 'endmodule\n')

    # Delete new lines and write only "endmodule""
    elif option == 3:
        init_line = get_index_of_line(topfile, '//vcd_dump')
        end_line = count_lines(topfile)

        remove_lines(topfile, init_line, end_line)
        append_unique_to_file(topfile, 'endmodule\n')    
    



