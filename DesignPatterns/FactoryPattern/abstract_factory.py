from abc import ABC, abstractmethod


class IButton(ABC):

    def __init__(self):
        pass

    @abstractmethod
    def press(self):
        pass


class MacButton(IButton):

    def __init__(self):
        super().__init__()

    def press(self):
        print("This is a Mac Button")


class WindowsButton(IButton):

    def __init__(self):
        super().__init__()

    def press(self):
        print("This is a Windows Button")

class ITextBox(ABC):
    def __init__(self):
        pass
    @abstractmethod
    def showText(self):
        pass

class MacTextBox(ITextBox):
    def __init__(self):
        super().__init__()
    def showText(self):
        print("Show Mac Text")

class WindowsTextBox(ITextBox):
    def __init__(self):
        super().__init__()
    def showText(self):
        print("Show Windows Text")

class IFactory(ABC):
    @abstractmethod
    def createButton(self):
        pass

    @abstractmethod
    def createTextBox(self):
        pass

class Windows(IFactory):
    def createButton(self):
        return WindowsButton()
    def createTextBox(self):
        return WindowsTextBox()


class Mac(IFactory):
    def createButton(self):
        return MacButton()
    def createTextBox(self):
        return MacTextBox()


class GuiFactory:
    @staticmethod
    def createFactory(os_type):
        if os_type == "windows":
            return Windows()
        elif os_type == "mac":
            return Mac()


if __name__ == "__main__":
    laptop = GuiFactory.createFactory("windows")

    button = laptop.createButton()
    button.press()
    text_box = laptop.createTextBox()
    text_box.showText()


