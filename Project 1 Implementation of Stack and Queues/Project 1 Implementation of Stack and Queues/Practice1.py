#Replication of Project 1 for Python practices

class listNode:
    def __init__(self, data):
        self.data = int(data)
        self.next = None

    def printNode(self, node, File):
        if node.next == None:
            File.write("(" + node.data.__str__() + ", NULL)-->")
        else:
            File.write("(" + node.data.__str__() + ', ' + node.next.data.__str__() + ")-->")


class LLstack(listNode):
    def __init__(self, top):
        self.top = top

    def push(self, node):
        node.next = self.top
        self.top = node

    def pop(self):
        if self.isEmpty():
            return None
        temp = self.top
        self.top = self.top.next
        return temp

    def isEmpty(self):
        return self.top.next == None

    def buildStack(self, inFile, outFile):
        for i in inFile:
            raw = i.split(' ')
            n = listNode(raw[1])
            if raw[0] == '+':
                self.push(n)
            else:
                junk = self.pop()
                if junk == None:
                    outFile.writelines("Stack is empty")
                else:
                    junk = None
            self.printStack(outFile)

    def printStack(self, out):
        out.write("Top -->")
        current = self.top.next
        while current is not None:
            current.printNode(current, out)
            current = current.next
        out.write("NULL\n")


class LLQueue(listNode):

    def __init__(self):
        dummyNode = listNode(-9999)
        self.head = dummyNode
        self.tail = dummyNode

    def buildQueue(self, inFile, outFile):
        for i in inFile:
            raw = i.split(' ')
            n = listNode(raw[1])
            if raw[0] == '+':
                self.insertQ(n)
            else:
                junk = self.deleteQ()
                if junk is None:
                    outFile.writelines("The Queue is Empty")
                else:
                    junk = None
            self.printQueue(outFile)

    def insertQ(self, node):
        self.tail.next = node
        self.tail = node

    def deleteQ(self):
        temp = self.head.next
        self.head.next = self.head.next.next
        return temp

    def isEmpty(self):
        return self.head.next is None

    def printQueue(self, out):
        current = self.head
        out.write("Front -->")
        while current is not None:
            current.printNode(current, out)
            current = current.next
        out.write("NULL\n")


class LLlist(listNode):

    def __init__(self):
        self.listHead = dummyNNode

    def buildList(self, inFile, outFile):
        for i in inFile:
            raw = i.split(' ')
            n = listNode(raw[1])
            if raw[0] == '+':
                self.listInsert(n)
            else:
                junk = self.deleteOneNode(int(raw[1]))
                if junk is None:
                    outFile.write("The data is not in the list\n")
                else:
                    junk = None
            self.printList(outFile)

    def listInsert(self, newNode):
        current = self.listHead
        while current.next is not None and current.next.data < newNode.data:
            current = current.next
        if current.data == newNode.data:
            newNode.next = current.next
            current.next = newNode
        else:
            newNode.next = current.next
            current.next = newNode

    def deleteOneNode(self, data):
        current = self.listHead.next
        while current.next is not None and current.next.data is not int(data):
            current = current.next
            if current.data < data:
                break
        if current.next.data == data and current.next is not None:
            temp = current.next
            current.next = current.next.next
            return temp
        return None

    def printList(self, out):
        out.write("listHead-->")
        current = self.listHead
        while current is not None:
            current.printNode(current, out)
            current = current.next
        out.write("NULL\n")


infile = open("random.txt", "r")
output = open("output.txt", "w")
output2 = open("output1.txt", "w")
output3 = open("output2.txt", "w")
dummyNNode = listNode(-9999)
stack = LLstack(dummyNNode)
queue = LLQueue()
stack.buildStack(infile, output)
infile.seek(0)
queue.buildQueue(infile, output2)
infile.seek(0)
list = LLlist()
list.buildList(infile, output3)

infile.close()
output.close()
output2.close()
output3.close()
