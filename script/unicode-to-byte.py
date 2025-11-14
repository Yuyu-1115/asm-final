PRINTABLE_ASCII_LB = ord(" ")
PRINTABLE_ASCII_UB = ord("~")

PREFIX = "0"
SUFFIX = "h"


def to_asm_declaration(var_name: str, text: str):
    res = []
    curr = ""

    for byte in text.encode("utf-8"):
        is_ascii = PRINTABLE_ASCII_LB <= byte <= PRINTABLE_ASCII_UB
        is_quote = byte in (34, 39, 96)  # " ' `

        if is_ascii or is_quote:
            res += chr(byte)
        else:
            # clear curr
            res.append(curr)
            curr = ""

            hex_val = f"{byte:02x}"
            res.append(f"{PREFIX}{hex_val}{SUFFIX}")

    if curr:
        res.append(curr)

    declaration_body = ",".join(res)

    return f"{var_name} DB {declaration_body}"


name = input()
data = input()
print(to_asm_declaration(name, data))
