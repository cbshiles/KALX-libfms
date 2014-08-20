html:
	pandoc --css ftap.css -H header.html -s --mathjax -i -t revealjs -o index.html ftap.md

latex:
	pandoc -r markdown+yaml_metadata_block -s -S --latex-engine=pdflatex \
	fms.md finance.md -o fms.tex

fms:
	pandoc -f markdown+definition_lists+example_lists \
	--css ftap.css -H header.html -s -S \
	--mathjax -o fms.html \
	background.md finance.md

rsync:
	rsync index.html kal@web69.webfaction.com:webapps/kalx/ftap

