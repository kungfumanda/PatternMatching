PATH_PATTERNS=./data/patts
PATH_TEXT=./data/text
EDIT_SIZE=0
ALG_LIST=('AhoCorasick' 'Ukkonen' 'BruteForce' 'KMP')

for alg in ${ALG_LIST[*]}; do
  echo $alg
  time ./pmt --count --algorithm $alg --edit $EDIT_SIZE --pattern $PATH_PATTERNS $PATH_TEXT
done

echo "grep"
grep  -c  -$EDIT_SIZE $PATH_PATTERNS $PATH_TEXT
