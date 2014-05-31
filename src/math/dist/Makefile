include $(ROOT)/src/top.mk

# make data as needed
normal_cdf.cpp: normal_cdf.dat
normal_cdf.dat: normal_cdf.sh
	normal_cdf.sh

normal_pdf.cpp: normal_pdf.dat
normal_pdf.dat: normal_pdf.sh
	normal_pdf.sh

clean::
	-rm -f *.dat

# r!make depends
test_prob.o: test_prob.cpp
test_normal_inv.o: test_normal_inv.cpp ../normal.h \
 $(ROOT)/include/ensure.h
