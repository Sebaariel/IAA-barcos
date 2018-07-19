import xlrd
import csv
import fileinput
from os import listdir
from os.path import isfile, join


def xls_to_csv():
    list_of_files = [f for f in listdir('instances') if isfile(join('instances', f))]
    for file_name in list_of_files:
        file_name = file_name[:-4]
        x =  xlrd.open_workbook('instances/'+file_name+'.xls')
        txtFile = open('instancesTxt/'+file_name+'.txt', 'wb')
        writecsv = csv.writer(txtFile, quoting=csv.QUOTE_ALL)

        sheets = x.sheet_names()
        sheets = reversed(sorted(sheets))

        for sheet in sheets:
            x1 = x.sheet_by_name(sheet)
            writecsv.writerow('-')
            for rownum in xrange(x1.nrows):
                writecsv.writerow(x1.row_values(rownum))

        txtFile.close()

        s = open('instancesTxt/'+file_name+'.txt').read()
        s = s.replace('"', '')
        f = open('instancesTxt/'+file_name+'.txt', 'w')
        f.write(s)
        f.close()

xls_to_csv()
