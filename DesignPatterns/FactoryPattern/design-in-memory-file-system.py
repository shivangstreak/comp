# https://leetcode.com/problems/design-in-memory-file-system/description/
from abc import ABC, abstractmethod
from typing import List

class FileStructure(ABC):

    @abstractmethod
    def get_type(self) -> bool:
        pass

    @abstractmethod
    def get_children(self) -> List[str]:
        pass

    def size(self) -> int:
        pass


class File(FileStructure):

    def __init__(self, name) -> None:
        self.name = name
        self.content = ""

    def get_type(self) -> str:
        return "File"

    def get_children(self) -> List[str]:
        return [self.name]

    def read(self) -> str:
        return self.content

    def write(self, val) -> None:
        self.content += val
        return


class Directory(FileStructure):

    def __init__(self, name="") -> None:
        self.name = name
        self.children = {}  # Name : FileStructure

    def get_type(self) -> str:
        return "Directory"

    def get_children(self):
        children = []
        for child in self.children.values():
            children.append(child.name)
        return sorted(children)

    def add_child(self, name, FileStructure):
        self.children[name] = FileStructure


class FileStructureManager(ABC):
    @abstractmethod
    def create(self, directory, path):
        pass


class FileManager(FileStructureManager):

    def create(self, directory, path) -> File:
        file = File(path)
        directory.add_child(path, file)
        return file


class DirectoryManager(FileStructureManager):

    def create(self, directory, path) -> Directory:
        if not path:
            return directory
        ptr_dir = directory
        for sp in path:
            dir = Directory(sp)
            ptr_dir.add_child(sp, dir)
            ptr_dir = dir
        return dir


class FileSystem:

    def __init__(self):
        self.root = Directory()
        self.filemgr = FileManager()
        self.dirmgr = DirectoryManager()

    def process_path(self, path):
        path = path.split("/")
        if path[-1] == "":
            path = path[:-1]
        return path[1:]

    def traverse_path(self, path):
        ptr = self.root
        ind = -1
        for ind, dir in enumerate(path):
            if dir not in ptr.children:
                break
            ptr = ptr.children[dir]
        return ind, ptr

    def ls(self, path: str) -> List[str]:
        path = self.process_path(path)
        _, ptr = self.traverse_path(path)
        return ptr.get_children()

    def mkdir(self, path: str) -> None:
        path = self.process_path(path)
        ind, ptr = self.traverse_path(path)
        self.dirmgr.create(ptr, path[ind:])

    def addContentToFile(self, filePath: str, content: str) -> None:
        path = self.process_path(filePath)
        ind, ptr = self.traverse_path(path)
        if ptr.get_type() != "File":
            dest_dir = self.dirmgr.create(ptr, path[ind:-1])
            file = self.filemgr.create(dest_dir, path[-1])
            file.write(content)
        else:
            ptr.write(content)

    def readContentFromFile(self, filePath: str) -> str:
        path = self.process_path(filePath)
        _, ptr = self.traverse_path(path)
        if ptr.get_type() != "File":
            return ""
        return ptr.read()

# Your FileSystem object will be instantiated and called as such:
# obj = FileSystem()
# param_1 = obj.ls(path)
# obj.mkdir(path)
# obj.addContentToFile(filePath,content)
# param_4 = obj.readContentFromFile(filePath)