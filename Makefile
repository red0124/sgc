include config.mk

install:
	@echo installing header files to ${DESTDIR}/${PREFIX}
	@mkdir -p ${DESTDIR}/${PREFIX}
	@cp -r lib/* ${DESTDIR}/${PREFIX}

uninstall:
	@echo removing header file ${DESTDIR}/${PREFIX}
	@rm -rf ${DESTDIR}/${PREFIX}
