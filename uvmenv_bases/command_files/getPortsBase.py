##########################
###    COMMAND FILE    ###
##########################

import cocotb

module_ports=None

@cocotb.test()
async def test_module(dut):
    for attr in dir(dut):
        if attr == '_sub_handles':
            module_ports = dut.__getattr__(attr)
            #print(dut.__getattr__(attr))
            #print(type(attr))
            break

    """print(module_ports)
    print(type(module_ports))

    print()
    print(type(module_ports.get('entrada')))
    # tamaño en bits
    print(len(module_ports.get('entrada')))

    print(type(module_ports.get('salida')))"""


    for port in module_ports:
        print(port, '=>', module_ports.get(port))
        


