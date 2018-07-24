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

        currentSheet = x.sheet_by_index(3)
        writecsv.writerow('-')
        for rownum in xrange(currentSheet.nrows):
            writecsv.writerow(currentSheet.row_values(rownum))

        currentSheet = x.sheet_by_index(1)
        writecsv.writerow('-')
        for rownum in xrange(currentSheet.nrows):
            writecsv.writerow(currentSheet.row_values(rownum))

        currentSheet = x.sheet_by_index(2)
        writecsv.writerow('-')
        writecsv.writerow('--')
        for rownum in xrange(currentSheet.nrows):
            writecsv.writerow(currentSheet.row_values(rownum))

        currentSheet = x.sheet_by_index(0)
        writecsv.writerow('-')
        for rownum in xrange(currentSheet.nrows):
            writecsv.writerow(currentSheet.row_values(rownum))

        txtFile.close()

        s = open('instancesTxt/'+file_name+'.txt').read()
        s = s.replace('"', '')
        f = open('instancesTxt/'+file_name+'.txt', 'w')
        f.write(s)
        f.close()

xls_to_csv()
