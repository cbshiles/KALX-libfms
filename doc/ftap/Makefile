MATHJAX="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"
#MATHJAX="MathJax-2.4-latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"

html:
	pandoc -s -i -H header.html --mathjax=${MATHJAX} -t revealjs -V theme:sky -V transition:slide -V center:false -o index.html ftap.md

opm:
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o opm.html opm.md
	pandoc -r markdown+yaml_metadata_block -s -S --latex-engine=pdflatex \
	opm.md -o opm.tex

xva:
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o xva.html xva.md
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o coc.html coc.md
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o cpd.html cpd.md
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o pcp.html pcp.md
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o fit.html fit.md
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o swd.html swd.md
	pandoc -s -i -H header.html --css ftap.css --mathjax=${MATHJAX} -o bsm.html bsm.md

latex:
	pandoc -r markdown+yaml_metadata_block -s -S --latex-engine=pdflatex \

fms:
	pandoc -f markdown+definition_lists+example_lists \
	--css ftap.css -H header.html -s -S \
	--mathjax -o fms.html \
	background.md finance.md

rsync:
	rsync *.html ftap.css kal@web69.webfaction.com:webapps/kalx/ftap

