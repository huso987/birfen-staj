class BankAccount:
    def __init__(self, account_number, owner_name, balance=0):
        self.account_number = account_number
        self.owner_name = owner_name
        self.balance = balance

    def deposit(self, amount):
        #para yatırma işlemi
        self.balance += amount
        print("Hesaba {} TL yatırıldı.".format(amount))

    def withdraw(self, amount):
        #para çekme işlemi
        if self.balance >= amount:
            self.balance -= amount
            print("Hesaptan {} TL çekildi.".format(amount))
        else:
            print("Yetersiz bakiye. Çekim işlemi gerçekleştirilemedi.")
    
    def display_info(self):
        #hesap bilgilerini görüntüleme
        print("Hesap Numarası:", self.account_number)
        print("Hesap Sahibi:", self.owner_name)
        print("Bakiye:", self.balance, "TL")

# BankAccount class ından bir hesab oluşturma
account1 = BankAccount("123456789", "Hüseyin Doğdu", 1200)
account1.display_info()
account1.deposit(500)
account1.withdraw(2000)
#yeni hesab bilgisi
account1.display_info()