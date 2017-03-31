from capstone import *


f = open("a.out","rb")
f.seek(3872)
bytes = f.read(66)
#CODE = b"\x55\x48\x8b\x05\xb8\x13\x00\x00"
md = Cs(CS_ARCH_X86, CS_MODE_64)
for i in md.disasm(bytes, 0x12):
         print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
