OBJS=plan.pdf
LATEX=xelatex

all: $(OBJS)

%.pdf: %.tex  %.bib
	$(LATEX) $(basename $@)
	bibtex  $(basename $@)
	$(LATEX) $(basename $@)
	$(LATEX) $(basename $@)

.PHONY: clean

clean:
	rm -f *.{aux,bbl,blg,pdf,log}
