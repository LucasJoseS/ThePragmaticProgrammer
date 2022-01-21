test: testDir cleanFile shebangFile commentFile shebangCommentFile
	echo "Test env: OK"

testDir:
	mkdir test -p

cleanFile:
	rm -f ./test/clean.pl
	touch ./test/clean.pl

shebangFile:
	echo "#!/usr/bin/env perl" > ./test/shebang.pl

commentFile:
	echo "# This is a comment" > ./test/comment.pl

shebangCommentFile:
	echo "#!/usr/bin/env perl" > ./test/shebangComment.pl
	echo "# Another Comment" >> ./test/shebangComment.pl
