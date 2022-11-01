RM := rm
GENERATE_PDF := pdflatex
OPEN_PDF := xdg-open
TARGET1 := relat.tex
TARGET2 := relat.pdf

.PHONY: all generate clean

all: clean generate open

open:
	@echo "[---Open pdf---]"
	@$(OPEN_PDF) $(TARGET2) $&

generate:
	@echo "[---Generating pdf---]"
	@$(GENERATE_PDF) $(TARGET1)

clean:
	@echo "[---Cleaning---]"
	@$(RM) -rfv $(TARGET2)
