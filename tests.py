import os

patts = {
    "dna": "ACACGTCGGTAACCAGTGCACAGGGAATCTGCTTCACAGCCGCCCCTCCCCTGCAGCAGGGAGGAGGTGTCACCAAAGCAGGGCCTGTCGGAGTCTCTGG",
    "english": "To Americans it is incredible that the class war should develop to such a pitch. But I have personall",
    "pitches": "0H?JAH?0G>7HG7F2HFA2E<5FE5D0FD0?3CDHC3O/JCOJ/A/JCJAMJAMJ8KH7HJ5K7JMG87HK<GA>?CH>JDAJ?CHJHAKCHJMGDKCH",
    "proteins": "QDCLCQMLDLVKPRTEGKITLQDLKRCKLANVFFDTFFNIEKYLDHEQKEQISLLRDGDSGGPELSDWEKYAAEEYDILVAEETAGEPWEDGFEAELSPV",
    "sources": "hile (xl_priv->xl_rx_ring[xl_priv->rx_ring_tail].framestatus & (RXUPDCOMPLETE | RXUPDFULL) ) { /* De",
    "dblp.xml": "<title>Performance Modelling and Comparisons of Global Shared Buffer Management Policies in a Cluste"
}

path_files = 'data/test_archive/'
#os.system("pmt --count --algorithm KMP --pattern ./data/patts ./data/text")

#test for exact match
for file in patts.keys():
    for alg in ["AhoCorasick", "BruteForce", "KMP", "Ukkonen", "Wumanber"]:
        print(f"-------------This is {alg} with {file} file--------------")
        for end in range(1,101):
            print("-------------------")
            print(file + " - " + alg + " - " + str(end))
            os.system(f"time pmt --count --algorithm {alg} --pattern {patts[file][0:end]} {path_files + file}")
        print(f"----------END of {alg} with {file} file---------------")