class Stare:
    def __init__(
        self,
        orar: dict[str, dict[(int,int),dict[str, (int, int)]]] | None = None,
    ) -> None:

        self.orar = orar

import utils
file = utils.read_yaml_file("/home/giulia/CTI/III/IA/tema1/inputs/dummy.yaml")
orar_init = {}
zile = file['Zile']
for i in zile:
    orar_init[i] = {(None, None): {None: (None, None)} }
init = Stare(orar=orar_init)
print(init.orar)

