import random  # 导入random模块以生成随机值。

def generate_data(rows):
    data = []  # 初始化一个空列表以存储生成的数据。

    for _ in range(rows):
        # 生成第一列的值，使用generate_first_column_value函数。
        first_column_value = generate_first_column_value()

        # 为其他列生成随机值。
        other_values = [
            round(random.uniform(10, 80), 2),      # 为第二列生成一个随机浮点数。
            random.randint(5, 70),                 # 为第三列生成一个随机整数。
            random.randint(60, 150),               # 为第四列生成一个随机整数。
            round(random.uniform(1.2, 4.6), 1),    # 为第五列生成一个随机浮点数。
            round(random.uniform(0.03, 0.12), 3),  # 为第六列生成一个随机浮点数。
            random.randint(0, 10)                  # 为第七列生成一个随机整数。
        ]

        # 将第一列的值与其他列的值组合成一行。
        row = [first_column_value] + other_values
        data.append(row)  # 将行附加到数据列表。

    return data  # 返回生成的数据。

def generate_first_column_value():
    letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'  # 定义一个包含大写字母的字符串。
    random_letter = random.choice(letters)  # 从字符串中选择一个随机字母。
    random_digits = ''.join(random.choices('0123456789', k=4))  # 生成一个随机的4位数字字符串。
    return f"{random_letter}{random_digits}"  # 将字母和数字连接成第一列的值。

def save_to_file(data, filename):
    with open(filename, 'w', encoding='utf-8') as file:
        for row in data:
            # 将每一行写入文件，将值转换为字符串并用空格连接。
            file.write(' '.join(map(str, row)) + '\n')

def main():
    rows = 10000  # 指定要生成的行数。
    data = generate_data(rows)  # 使用generate_data函数生成数据。

    # 打印生成的数据，用空格分隔值。
    for row in data:
        print(' '.join(map(str, row)))

    # 将生成的数据保存到名为"商品销售情况.txt"的文件中。
    save_to_file(data, "商品销售情况.txt")

if __name__ == "__main__":
    main()
