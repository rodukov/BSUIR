import math

def raschet_tokov():
    E1 = float(input("Введите значения источников ЭДС в В:\nE1 = "))
    E3 = float(input("E3 = "))

    R = [0] * 7
    print("\nВведите значения сопротивлений в кОм:")
    for i in range(1, 7):
        R[i] = float(input(f"R{i} = ")) * 1000

    # Расчет при действии только E1
    R34 = R[3] * R[4] / (R[3] + R[4])
    R2346 = R[2] + R34 + R[6]
    R23456 = R[5] * R2346 / (R[5] + R2346)
    Rekv1 = R[1] + R23456
    I11 = E1 / Rekv1
    I55 = R2346 * I11 / (R[5] + R2346)
    I22 = I11 - I55
    I66 = I22
    I44 = R[3] * I22 / (R[3] + R[4])
    I33 = I22 - I44

    print(f"R34 = {R34} Ом")
    print(f"R2346 = {R2346} Ом")
    print(f"R23456 = {R23456} Ом")
    print(f"Rэкв1 = {Rekv1} Ом\n")
    print("Токи в ветвях без источника ЭДС E3:")
    print(f"I1' = {I11} мА")
    print(f"I5' = {I55} мА")
    print(f"I2' = I6' = {I22} мА")
    print(f"I4' = {I44} мА")
    print(f"I3' = {I33} мА\n")

    # Расчет при действии только E3
    R15 = R[1] * R[5] / (R[1] + R[5])
    R1256 = R15 + R[2] + R[6]
    R12456 = R1256 * R[4] / (R1256 + R[4])
    Rekv2 = R12456 + R[3]
    I333 = E3 / Rekv2
    I444 = R1256 / (R1256 + R[4]) * I333
    I222 = I333 - I444
    I666 = I222
    I555 = R[1] / (R[1] + R[5]) * I222
    I111 = I222 - I555

    print(f"R15 = {R15} Ом")
    print(f"R1256 = {R1256} Ом")
    print(f"R12456 = {R12456} Ом")
    print(f"Rэкв2 = {Rekv2} Ом\n")
    print("Токи в ветвях без источника ЭДС E1:")
    print(f"I1'' = {I111} мА")
    print(f"I5'' = {I555} мА")
    print(f"I2'' = I6'' = {I222} мА")
    print(f"I4'' = {I444} мА")
    print(f"I3'' = {I333} мА\n")

    # Суммарные токи
    I1 = I11 - I111
    I2 = I22 - I222
    I6 = I2
    I3 = I333 - I33
    I4 = I44 + I444
    I5 = I55 + I555

    print("Расчет суммарных токов:")
    print(f"I1 = {I1} мА")
    print(f"I2 = I6 = {I2} мА")
    print(f"I3 = {I3} мА")
    print(f"I4 = {I4} мА")
    print(f"I5 = {I5} мА\n")

    # Баланс мощностей
    P_left = (I1**2)*R[1] + (I2**2)*R[2] + (I3**2)*R[3] + (I4**2)*R[4] + (I5**2)*R[5] + (I6**2)*R[6]
    P_right = E1*I1 + E3*I3
    print("Баланс мощностей:")
    print(f"{P_left} = {P_right}")

if __name__ == "__main__":
    raschet_tokov()
