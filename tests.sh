PATH_PATTERNS=./data/patts
PATH_TEXT=./data/text
EDIT_SIZE=1
ALG_LIST=('AhoCorasick' 'WuManber' 'Ukkonen' 'BruteForce' 'KMP')

for alg in ${ALG_LIST[*]}; do
  echo $alg
  time ./pmt --count --algorithm $alg --edit $EDIT_SIZE --pattern $PATH_PATTERNS $PATH_TEXT
done

./pmt --count --algorithm AhoCorasick --pattern ./data/patts ./data/text

echo "grep"
time grep  -c  -$EDIT_SIZE $PATH_PATTERNS $PATH_TEXT
