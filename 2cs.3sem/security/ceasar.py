# caesar_russian.py — перебор сдвигов для русской азбуки (включая Ё/ё)

alphabet_upper = list("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ")
alphabet_lower = list("абвгдеёжзийклмнопрстуфхцчшщъыьэюя")

def caesar_decrypt(text, shift):
    res = []
    for ch in text:
        if ch in alphabet_upper:
            idx = alphabet_upper.index(ch)
            res.append(alphabet_upper[(idx - shift) % len(alphabet_upper)])
        elif ch in alphabet_lower:
            idx = alphabet_lower.index(ch)
            res.append(alphabet_lower[(idx - shift) % len(alphabet_lower)])
        else:
            # сохраняем пробелы, пунктуацию, цифры и т.д.
            res.append(ch)
    return "".join(res)

cipher = """Йё. Сщэюк хфрсфуешвче йёууфчшо ч щжфиото кл ткцосёто, рфшфцбк хфшфт
йф рцёпуфчшо, хфчсщмёш йсе шкже хкцосёто (ыфше о ук фчфжф эочшбто),
щйкцмозёдяото з цёзуфзкчоо шзфо ыцфтёдяок очшоуб уё гшфп збякцжскууфп
скчшуоьк."""

# Перебор всех возможных сдвигов
for s in range(1, len(alphabet_lower)):  # сдвиг 1..32 (всего 33 буквы)
    dec = caesar_decrypt(cipher, s)
    print(f"Сдвиг {s}:\n{dec}\n{'-'*60}\n")
