HTML = lesson1.html

all: index.html $(HTML)

$(HTML): %.html: %.md
	pandoc -S -H header.html -B before.html -A after.html $< -o $@

index.html: index.md
	pandoc -S -H header.html -A after.html $< -o $@

$(HTML): header.html before.html after.html

clean:
	rm -f $(HTML)
