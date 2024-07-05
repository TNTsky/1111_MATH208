# Convert a date in yyyy/mm/dd into “name of the month” dd, yyyy
# date: 2022/09/07


# 月份名稱
months = ["January", "February", "March", "April",
          "May", "June", "July", "August",
          "September", "October", "November", "December"]


# 轉換函式:將字串以"/"分割成列表,並以特定格式打印出
def convert(date):
    Date = date.split("/")
    print(f'{months[int(Date[1])-1]} {int(Date[2])}, {Date[0]}.')


# 以迴圈重複執行函數操作
while True:
    convert(input("(yyyy/mm/dd) : "))
