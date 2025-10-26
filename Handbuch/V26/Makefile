# V26 Handbuch – Pylovara + MCS + AIMS + BMC
# Ziel: PDF mit tectonic + pandoc aus Markdown + LaTeX

PDF_OUTPUT = V26_Pylovara_System_AI.pdf
TEMPLATE  = template/pylovara.latex
SRC_DIR   = src
SRC_MD    = $(wildcard $(SRC_DIR)/*.md)
METADATA  = metadata.yaml

.PHONY: pdf clean setup

setup:
	mkdir -p $(SRC_DIR) template images

pdf: $(PDF_OUTPUT)

$(PDF_OUTPUT): $(SRC_MD) $(METADATA) $(TEMPLATE)
	pandoc \
		--from markdown+yaml_metadata_block \
		--to latex \
		--template=$(TEMPLATE) \
		--pdf-engine=tectonic \
		--output=$@ \
		$(SRC_MD)

clean:
	rm -f $(PDF_OUTPUT)

