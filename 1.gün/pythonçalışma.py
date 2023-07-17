def calculate_average(nums):
    total = sum(nums)
    average = total / len(nums)
    return average
num_list = []
n = int(input("Kaç sayi gireceksiniz? "))
for i in range(n):
    num = float(input("Sayi {}: ".format(i+1)))
    num_list.append(num)

avg = calculate_average(num_list)
print("Girilen sayilarin ortalamasi:", avg)
