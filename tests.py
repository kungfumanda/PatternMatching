import os

path_files = './data/test_archive/'

# padrões definidos com base aleatória entre os textos testados
patts = {
    #"dna": "ACACGTCGGTAACCAGTGCACAGGGAATCTGCTTCACAGCCGCCCCTCCCCTGCAGCAGGGAGGAGGTGTCACCAAAGCAGGGCCTGTCGGAGTCTCTGG",
    #"english": "To Americans it is incredible that the class war should develop to such a pitch. But I have personall",
    "pitches": "0H?JAH?0G>7HG7F2HFA2E<5FE5D0FD0?3CDHC3O/JCOJ/A/JCJAMJAMJ8KH7HJ5K7JMG87HK<GA>?CH>JDAJ?CHJHAKCHJMGDKCH",
    #"proteins": "QDCLCQMLDLVKPRTEGKITLQDLKRCKLANVFFDTFFNIEKYLDHEQKEQISLLRDGDSGGPELSDWEKYAAEEYDILVAEETAGEPWEDGFEAELSPV",
    "sources": "hile (xl_priv->xl_rx_ring[xl_priv->rx_ring_tail].framestatus & (RXUPDCOMPLETE | RXUPDFULL) ) { /* De",
    #"dblp.xml": "<title>Performance Modelling and Comparisons of Global Shared Buffer Management Policies in a Cluste"
}

# Testes para casamento exato de padrões 
# Variando o tamanho do prefixo do padrão de 1 até 100, testa todos os algoritmos do projeto e o grep
for file in patts.keys():
    for alg in ["AhoCorasick", "BruteForce", "KMP", "Ukkonen", "WuManber", "grep"]:
        print(f"-------------This is {alg} with {file} file-------------")
        for end in range(1,101):
            print("-------------")
            print(f"{alg} - {file} - pattern lenght: {str(end)}")
            if (alg != "grep"):
                os.system(f"time ./bin/pmt --count --algorithm {alg} \"{patts[file][0:end]}\" {path_files + file}")
            else:
                os.system(f"time grep -c \"{patts[file][0:end]}\" {path_files + file}")
        print(f"-------------END of {alg} with {file} file-------------")


# Testes para casamento aproximado de padrões
# Utiliza padrão de erro variante entre 0 e m-1 (m sendo tamanho do padrão), no nosso caso, padrão fixo de tamanho 16
for file in patts.keys():
    for alg in ["WuManber", "Ukkonen", "agrep"]:
        print(f"-------------This is {alg} with {file} file-------------")
        for r in range(0, 16):
            print("-------------")
            print(f"{alg} - {file} - edit: {str(r)}")
            print(r, len(patts[file][0:16]))
            if (alg != "agrep"):
                os.system(f"time ./bin/pmt --count --edit {r} --algorithm {alg} \"{patts[file][0:16]}\" {path_files + file}")
            else:
                os.system(f"time agrep -c {str(r)} \"{patts[file][0:16]}\" {path_files + file}")
        print(f"-------------END of {alg} with {file} file-------------")