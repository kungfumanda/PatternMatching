PATH_PATTERNS=./data/patts
PATH_TEXT=./data/text
EDIT_SIZE=1
ALG_LIST=('AhoCorasick' 'WuManber' 'Ukkonen' 'BruteForce' 'KMP' 'default')

for alg in ${ALG_LIST[*]}; do
  echo $alg
  time ./bin/pmt --count --algorithm $alg --edit $EDIT_SIZE --pattern $PATH_PATTERNS $PATH_TEXT
done

echo "grep"
time grep  -c  -$EDIT_SIZE $PATH_PATTERNS $PATH_TEXT
