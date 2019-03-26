class LogicElement:
    """
    создан суперкласс содержащий в себе логику изложения материала
    логический элемент это все то к чему существует таблица истинности
    """
    def __init__(self, input_size, state_size, output_size):
        self.input = [0] * input_size
        self.state = [0] * state_size
        self.output = [0] * output_size

    def push_state(self, key):
        for o, s, k in zip(self.output, self.state, key):
            o.input[k] = s


class AND (LogicElement):
    def __init__(self):
        LogicElement.__init__(self, 2, 1, 1)

    def compute_state(self):
        if self.input[0] + self.input[1] == 2:
            self.state[0] = 1
        else:
            self.state[0] = 0


class NOT (LogicElement):
    def __init__(self):
        LogicElement.__init__(self,1,1,1)

    def compute_state(self):
        if self.input[0] == 0:
            self.state[0] = 1
        else:
            self.state[0] = 0


class OR (LogicElement):
    def __init__(self):
        LogicElement.__init__(self, 2, 1, 2)

    def compute_state(self):
        if self.input[0] + self.input[1] != 0:
            self.state[0] = 1
        else:
            self.state[0] = 0


class MUX (LogicElement):
    """
    input: A B SEL from
    https://www-users.cs.york.ac.uk/~mjf/simple_cpu/

    """
    def __init__(self):
        LogicElement.__init__(self,3,1,1)  #A B SEL

    def compute_state(self):
        inv1 = NOT()
        and1 = AND()
        and2 = AND()
        or1 = OR()

        inv1.output[0] = and1
        and1.output[0] = or1
        and2.output[0] = or1

        and2.input[0] = self.input[2]
        and2.input[1] = self.input[1]
        and2.compute_state()
        and2.push_state([1])

        inv1.input[0] = self.input[2]
        inv1.compute_state()
        inv1.push_state([1])

        and1.input[0] = self.input[0]
        and1.compute_state()
        and1.push_state([0])

        or1.compute_state()

        self.state = or1.state


class byte:
    """
    потенциальная структура данных которая может быть использована для
    приема и передачи значений между байтовыми логическими элементами
    например мультиплексера
    """
    def __init__(self):
        self.bits = [0]*8


class XOR (LogicElement):
    def __init__(self):
        LogicElement.__init__(self, 2,1,1)

    def compute_state(self):
        if self.input[0] + self.input[1] == 1:
            self.state[0] = 1
        else:
            self.state[0] = 0


class MUX_8bit (LogicElement):
    """
    функция возвращает 1 байт из двух входящих, в зависимости от значения

    """
    def __init__(self):
        # A(7:0) B(7:0) SEL
        LogicElement.__init__(self,17,8,8)

    def compute_state(self):
        v = []
        for i in range(8):
            v.append(MUX())
            v[i].input[0] = self.input[i]
            v[i].input[1] = self.input[8+i]
            v[i].input[2] = self.input[16]

        for i in range(8):
            v[i].compute_state()
            self.state[i] = v[i].state[0]


class Half_Adder (LogicElement):
    """
    self.state[0] == COUNT
    self.state[1] == SUM
    """
    def __init__(self):
        LogicElement.__init__(self,2,2,2)

    def compute_state(self):
        and1 = AND()
        xor1 = XOR()

        and1.input[0] = self.input[0]
        and1.input[1] = self.input[1]

        xor1.input[0] = self.input[0]
        xor1.input[1] = self.input[1]

        and1.compute_state()
        xor1.compute_state()

        self.state[0] = and1.state[0]  #COUNT
        self.state[1] = xor1.state[0]  #SUM


class Full_Adder (LogicElement):
    def __init__(self):
        # A B Cin
        LogicElement.__init__(self, 3, 2, 2)

    def compute_state(self):
        # A B Cin  подается на вход
        ha1 = Half_Adder()
        ha2 = Half_Adder()
        or1 = OR()



        ha1.input = [self.input[0],self.input[1]]
        ha1.output = [or1, ha2]
        ha1.compute_state()
        ha1.push_state([0,0])

        ha2.output = [or1]
        ha2.input[1] = self.input[2]
        ha2.compute_state()
        ha2.push_state([1])

        or1.compute_state()

        self.state = [or1.state[0], ha2.state[1]]


class Full_Adder_8bit(LogicElement):
    def __init__(self):
        LogicElement.__init__(self,17,9,9)

    def compute_state(self):
        v = []
        for i in range(8):
            v.append(Full_Adder())
            v[i].input[0] = self.input[i]
            v[i].input[1] = self.input[i+8]
            v[i].input[2] = self.input[16]

        for i in range(7):
            v[i].output = v[i+1]

        for i in range(8):
            v[i].compute_state()

        for i in range(8):
            self.state[i] = v[i].state[0]
        self.state[8] = v[7].state[1]



def bit_to_int(li):
    result = 0
    for i in range(8):
        result += li[i] * (2**(7-i))

    return  result


if __name__ == "__main__":
    fa8 = Full_Adder_8bit()
    n123 = [0,1,1,1,1,0,1,1]
    nM45 = [1,1,0,1,0,0,1,1]
    n45 =  [0,0,1,0,1,1,0,1]

    a = [0,0,0,0,0,1,1,0]
    #print(bit_to_int(a))
    fa8.input = [*a, *a, 1]
    fa8.compute_state()
    print(fa8.state)




# 1 4 8 32 = 45
# 1 2 8 16 32 64 = 27, 59, 123