from classic_bot import ClassicBot


class WareHouse:
    def __init__(self, poll_count, commands, bot_cap):
        self.poll_count = poll_count
        self.commands = commands
        self.bot_cap = bot_cap

        # multiple types of bot those classification can go here!!!
        self.bot = ClassicBot(self)


commands = "PLMML"
number_of_polls_in_ware_house = 10

bot_cap = 5
# Driver function (This can be put in a diff module too)
# For simplicity I have put it here!!

ware_obj_1 = WareHouse(number_of_polls_in_ware_house, commands, bot_cap)

result = ware_obj_1.bot.calculate_result()
print(result)
