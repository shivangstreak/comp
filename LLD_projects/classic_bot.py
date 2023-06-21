from bot_base import BotBase

class ClassicBot(BotBase):
    def __init__(self, ware_house):
        super(ClassicBot, self).__init__(ware_house)

    # core logic goes here , this function will calculate how many boxes are places
    def calculate_result(self):
        "PLMML"
        result = {}
        position = 0
        how_many_dist_uptil_now = 0
        for command in self.ware_house.commands:
            if command == "P":
                # reset the position
                position = 0
            elif command == "L":
                if how_many_dist_uptil_now > self.capacity:
                    #reset position again
                    return "Error to user saying my cap is over"
                else:
                    if result.get(position):
                        result[position] = result.get(position) + 1
                        how_many_dist_uptil_now = how_many_dist_uptil_now + 1
                    else:
                        #first time making the key
                        result[position] = 1
                        how_many_dist_uptil_now = how_many_dist_uptil_now + 1
            else:
                # This is the case of "M" , move the counter
                position = position + 1
        return result