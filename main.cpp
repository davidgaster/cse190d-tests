#include <iostream>
#include <stdlib.h>
//#include <stdio.h>
#include <cstring>
#include <memory>
#include "page.h"
#include "buffer.h"
#include "file_iterator.h"
#include "page_iterator.h"
#include "exceptions/file_not_found_exception.h"
#include "exceptions/invalid_page_exception.h"
#include "exceptions/page_not_pinned_exception.h"
#include "exceptions/page_pinned_exception.h"
#include "exceptions/buffer_exceeded_exception.h"

#define PRINT_ERROR(str) \
{ \
	std::cerr << "On Line No:" << __LINE__ << "\n"; \
	std::cerr << str << "\n"; \
	exit(1); \
}

using namespace badgerdb;

const PageId num = 100;
PageId pid[num], pageno1, pageno2, pageno3, i;
RecordId rid[num], rid2, rid3;
Page *page, *page2, *page3;
char tmpbuf[100];
BufMgr* bufMgr;
File *file1ptr, *file2ptr, *file3ptr, *file4ptr, *file5ptr,
     *file7ptr, *file8ptr, *file9ptr, *file10aptr, *file10bptr,
		 *file11ptr, *file12ptr;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();

// Our tests
void test7();
void test8a();
void test8b();
void test9();
void test10(); 
void test11();
void testBufMgr();

int main() 
{
	//Following code shows how to you File and Page classes

  const std::string& filename = "test.db";
  // Clean up from any previous runs that crashed.
  try
	{
    File::remove(filename);
  }
	catch(FileNotFoundException)
	{
  }

  {
    // Create a new database file.
    File new_file = File::create(filename);
    
    // Allocate some pages and put data on them.
    PageId third_page_number;
    for (int i = 0; i < 5; ++i) {
      Page new_page = new_file.allocatePage();
      if (i == 3) {
        // Keep track of the identifier for the third page so we can read it
        // later.
        third_page_number = new_page.page_number();
      }
      new_page.insertRecord("hello!");
      // Write the page back to the file (with the new data).
      new_file.writePage(new_page);
    }

    // Iterate through all pages in the file.
    for (FileIterator iter = new_file.begin();
         iter != new_file.end();
         ++iter) {
      // Iterate through all records on the page.
      for (PageIterator page_iter = (*iter).begin();
           page_iter != (*iter).end();
           ++page_iter) {
        std::cout << "Found record: " << *page_iter
            << " on page " << (*iter).page_number() << "\n";
      }
    }

    // Retrieve the third page and add another record to it.
    Page third_page = new_file.readPage(third_page_number);
    const RecordId& rid = third_page.insertRecord("world!");
    new_file.writePage(third_page);

    // Retrieve the record we just added to the third page.
    std::cout << "Third page has a new record: "
        << third_page.getRecord(rid) << "\n\n";
  }
  // new_file goes out of scope here, so file is automatically closed.

  // Delete the file since we're done with it.
  File::remove(filename);

	//This function tests buffer manager, comment this line if you don't wish to test buffer manager
	testBufMgr();
}

void testBufMgr()
{
	// create buffer manager
	bufMgr = new BufMgr(num);

	// create dummy files
  const std::string& filename1 = "test.1";
  const std::string& filename2 = "test.2";
  const std::string& filename3 = "test.3";
  const std::string& filename4 = "test.4";
  const std::string& filename5 = "test.5";
	const std::string& filename7 = "test.7";
  const std::string& filename8 = "test.8";
  const std::string& filename9 = "test.9";
  const std::string& filename10a = "test.10a";
  const std::string& filename10b = "test.10b";
	const std::string& filename11 = "test.11";
  const std::string& filename12 = "test.12";

  try
	{
    File::remove(filename1);
    File::remove(filename2);
    File::remove(filename3);
    File::remove(filename4);
    File::remove(filename5);
		File::remove(filename7);
    File::remove(filename8);
    File::remove(filename9);
    File::remove(filename10a);
    File::remove(filename10b);
		File::remove(filename11);
    File::remove(filename12);
  }
	catch(FileNotFoundException e)
	{
  }

	File file1 = File::create(filename1);
	File file2 = File::create(filename2);
	File file3 = File::create(filename3);
	File file4 = File::create(filename4);
	File file5 = File::create(filename5);
	File file7 = File::create(filename7);
	File file8 = File::create(filename8);
	File file9 = File::create(filename9);
	File file10a = File::create(filename10a);
	File file10b = File::create(filename10b);
	File file11 = File::create(filename11);
	File file12 = File::create(filename12);

	file1ptr = &file1;
	file2ptr = &file2;
	file3ptr = &file3;
	file4ptr = &file4;
	file5ptr = &file5;
	file7ptr = &file7;
	file8ptr = &file8;
	file9ptr = &file9;
	file10aptr = &file10a;
	file10bptr = &file10b;
	file11ptr = &file11;
	file12ptr = &file12;

	//Test buffer manager
	//Comment tests which you do not wish to run now. Tests are dependent 
	//on their preceding tests. So, they have to be run in the following order. 
	//Commenting  a particular test requires commenting all tests that follow 
	//it else those tests would fail.
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

	// Our tests
	test7();
	test8a(); 
	test8b(); 
	test9(); 
	test10(); 
	test11();

	//Close files before deleting them
	file1.~File();
	file2.~File();
	file3.~File();
	file4.~File();
	file5.~File();
	file7.~File();
	file8.~File();
	file9.~File();
	file10a.~File();
	file10b.~File();
	file11.~File();
	file12.~File();


	delete bufMgr;

	//Delete files
	File::remove(filename1);
	File::remove(filename2);
	File::remove(filename3);
	File::remove(filename4);
	File::remove(filename5);
	File::remove(filename7);
	File::remove(filename8);
	File::remove(filename9);
	File::remove(filename10a);
	File::remove(filename10b);
	File::remove(filename11);
	File::remove(filename12);

	std::cout << "\n" << "Passed all tests." << "\n";
}

void test1()
{
	//Allocating pages in a file...
	for (i = 0; i < num; i++)
	{
		// allocates page and stores the page number in pid[i]
		bufMgr->allocPage(file1ptr, pid[i], page);
		
		// builds record string, inserts record in the page
		sprintf((char*)tmpbuf, "test.1 Page %d %7.1f", pid[i], (float)pid[i]);
		rid[i] = page->insertRecord(tmpbuf);

		// unpins page
		bufMgr->unPinPage(file1ptr, pid[i], true);
	}

	//Reading pages back...
	for (i = 0; i < num; i++)
	{
		bufMgr->readPage(file1ptr, pid[i], page);
		sprintf((char*)&tmpbuf, "test.1 Page %d %7.1f", pid[i], (float)pid[i]);
		if(strncmp(page->getRecord(rid[i]).c_str(), tmpbuf, strlen(tmpbuf)) != 0)
		{
			PRINT_ERROR("ERROR :: CONTENTS DID NOT MATCH");
		}
		bufMgr->unPinPage(file1ptr, pid[i], false);
	}
	std::cout<< "Test 1 passed" << "\n";
}

void test2()
{
	//Writing and reading back multiple files
	//The page number and the value should match

	for (i = 0; i < num/3; i++) 
	{
		bufMgr->allocPage(file2ptr, pageno2, page2);
		sprintf((char*)tmpbuf, "test.2 Page %d %7.1f", pageno2, (float)pageno2);
		rid2 = page2->insertRecord(tmpbuf);

		int index = random() % num;
    pageno1 = pid[index];
		bufMgr->readPage(file1ptr, pageno1, page);
		sprintf((char*)tmpbuf, "test.1 Page %d %7.1f", pageno1, (float)pageno1);
		if(strncmp(page->getRecord(rid[index]).c_str(), tmpbuf, strlen(tmpbuf)) != 0)
		{
			PRINT_ERROR("ERROR :: CONTENTS DID NOT MATCH");
		}

		bufMgr->allocPage(file3ptr, pageno3, page3);
		sprintf((char*)tmpbuf, "test.3 Page %d %7.1f", pageno3, (float)pageno3);
		rid3 = page3->insertRecord(tmpbuf);

		bufMgr->readPage(file2ptr, pageno2, page2);
		sprintf((char*)&tmpbuf, "test.2 Page %d %7.1f", pageno2, (float)pageno2);
		if(strncmp(page2->getRecord(rid2).c_str(), tmpbuf, strlen(tmpbuf)) != 0)
		{
			PRINT_ERROR("ERROR :: CONTENTS DID NOT MATCH");
		}

		bufMgr->readPage(file3ptr, pageno3, page3);
		sprintf((char*)&tmpbuf, "test.3 Page %d %7.1f", pageno3, (float)pageno3);
		if(strncmp(page3->getRecord(rid3).c_str(), tmpbuf, strlen(tmpbuf)) != 0)
		{
			PRINT_ERROR("ERROR :: CONTENTS DID NOT MATCH");
		}

		bufMgr->unPinPage(file1ptr, pageno1, false);
	}

	for (i = 0; i < num/3; i++) {
		bufMgr->unPinPage(file2ptr, i+1, true);
		bufMgr->unPinPage(file2ptr, i+1, true);
		bufMgr->unPinPage(file3ptr, i+1, true);
		bufMgr->unPinPage(file3ptr, i+1, true);
	}

	bufMgr->flushFile(file2ptr);
	std::cout << "Test 2 passed" << "\n";
}

void test3()
{
	try
	{
		bufMgr->readPage(file4ptr, 1, page);
		PRINT_ERROR("ERROR :: File4 should not exist. Exception should have been thrown before execution reaches this point.");
	}
	catch(InvalidPageException e)
	{
	}

	std::cout << "Test 3 passed" << "\n";
}

void test4()
{
	bufMgr->allocPage(file4ptr, i, page);
	bufMgr->unPinPage(file4ptr, i, true);
	try
	{
		bufMgr->unPinPage(file4ptr, i, false);
		PRINT_ERROR("ERROR :: Page is already unpinned. Exception should have been thrown before execution reaches this point.");
	}
	catch(PageNotPinnedException e)
	{
	}

	std::cout << "Test 4 passed" << "\n";
}

void test5()
{
	for (i = 0; i < num; i++) {
		bufMgr->allocPage(file5ptr, pid[i], page);
		sprintf((char*)tmpbuf, "test.5 Page %d %7.1f", pid[i], (float)pid[i]);
		rid[i] = page->insertRecord(tmpbuf);
	}

	PageId tmp;
	try
	{
		bufMgr->allocPage(file5ptr, tmp, page);
		PRINT_ERROR("ERROR :: No more frames left for allocation. Exception should have been thrown before execution reaches this point.");
	}
	catch(BufferExceededException e)
	{
	}

	std::cout << "Test 5 passed" << "\n";

	for (i = 1; i <= num; i++)
		bufMgr->unPinPage(file5ptr, i, true);
}

void test6()
{
	//flushing file with pages still pinned. Should generate an error
	for (i = 1; i <= num; i++) {
		bufMgr->readPage(file1ptr, i, page);
	}

	try
	{
		bufMgr->flushFile(file1ptr);
		PRINT_ERROR("ERROR :: Pages pinned for file being flushed. Exception should have been thrown before execution reaches this point.");
	}
	catch(PagePinnedException e)
	{
	}

	std::cout << "Test 6 passed" << "\n";

	for (i = 1; i <= num; i++) 
		bufMgr->unPinPage(file1ptr, i, true);

	bufMgr->flushFile(file1ptr);
}

// Allocate pages, flush to disk and read back
void test7()
{
	// file1 has been flushed from test6

	// Allocating pages again in file1
	for (i = 0; i < num; i++)
	{
		// allocates page and stores the page number in pid[i]
		bufMgr->allocPage(file7ptr, pid[i], page);
		
		// builds record string, inserts record in the page
		sprintf((char*)tmpbuf, "test.7 Page %d %7.1f", pid[i], (float)pid[i]);
		rid[i] = page->insertRecord(tmpbuf);

		// unpins all pages
		bufMgr->unPinPage(file7ptr, pid[i], true);
	}

	try
	{
		bufMgr->flushFile(file7ptr);
	}
	catch(PagePinnedException e)
	{
		PRINT_ERROR("ERROR :: In flushFile(). All pages should be been unpinned!");
	}

	//Reading pages back...
	for (i = 0; i < num; i++)
	{
		bufMgr->readPage(file7ptr, pid[i], page);
		sprintf((char*)&tmpbuf, "test.7 Page %d %7.1f", pid[i], (float)pid[i]);
		if(strncmp(page->getRecord(rid[i]).c_str(), tmpbuf, strlen(tmpbuf)) != 0)
		{
			PRINT_ERROR("ERROR :: CONTENTS DID NOT MATCH");
		}
		bufMgr->unPinPage(file7ptr, pid[i], false);
	}

	// Flush file 1 so we can use it for more tests
	try
	{
		bufMgr->flushFile(file7ptr);
	}
	catch(PagePinnedException e)
	{
		PRINT_ERROR("ERROR :: In flushFile(). All pages should be been unpinned!");
	}

	std::cout<< "Test 7 passed" << "\n";
}

// Read pages after pages has been disposed
// Throws buffer invalid page exception
void test8a()
{
	// Allocating num pages
	for (i = 0; i < num; i++)
	{
		bufMgr->allocPage(file8ptr, pid[i], page); 
	}
	// Alloc num + 1 page
	try {
		bufMgr->allocPage(file8ptr, pid[i], page); 
		PRINT_ERROR("ERROR :: Buffer should have overflowed and thrown BufferExceededException!");
	}
	catch (BufferExceededException) {

	}

	// reset file1 in bufpool
	for (i = 0; i < num; i++)
	{
		bufMgr->unPinPage(file8ptr, pid[i], false);
	}
	bufMgr->flushFile(file8ptr);
	std::cout<< "Test 8a passed" << "\n";

}

// Allocate pages that are more than available
// space in buffer pool and read back
// Throws buffer exceeded exception!
void test8b()
{
	// Allocating num pages, but does not unpin them.
	for (i = 0; i < num; i++)
	{
		bufMgr->allocPage(file8ptr, pid[i], page);
	}

	// Reads one more page, implicitly alloc > num pages
	try {
		bufMgr->readPage(file8ptr, pid[i], page); // implicity calls allocPage
		PRINT_ERROR("ERROR :: Buffer should have overflowed and thrown BufferExceededException!");
	}
	catch (BufferExceededException) {

	}
	
	// reset file1 in bufpool
	for (i = 0; i < num; i++)
	{
		bufMgr->unPinPage(file8ptr, pid[i], false);
	}
	bufMgr->flushFile(file8ptr);

	std::cout<< "Test 8b passed" << "\n";

}

// Read pages after pages have been disposed
// Throws buffer invalid page exception
void test9()
{
	for (i = 0; i < num; i++)
	{
		bufMgr->allocPage(file9ptr, pid[i], page);
		// builds record string, inserts record in the page
		sprintf((char*)tmpbuf, "test.9 Page %d %7.1f", pid[i], (float)pid[i]);
		rid[i] = page->insertRecord(tmpbuf);

		// dispose all pages
		bufMgr->disposePage(file9ptr, pid[i]);
	}

	for (i = 0; i < num; i++)
	{
		try {
			bufMgr->readPage(file9ptr, pid[i], page);
			PRINT_ERROR("ERROR :: Page should not have been able to be read since it was disposed.");
		}
		catch (InvalidPageException) {

		}
	}
	
	std::cout<< "Test 9 passed" << "\n";
}

// Read pages after allocating pages for another file
// Should throw Invalid Page Exception
void test10() {

	// Allocating, reading pages in file10a in slots 0-49
	for (i = 0; i < num; i++)
	{
		bufMgr->allocPage(file10aptr, pid[i], page);

		// builds record string, inserts record in the page
		sprintf((char*)tmpbuf, "test.10 Page %d %7.1f", pid[i], (float)pid[i]);
		rid[i] = page->insertRecord(tmpbuf);
		bufMgr->unPinPage(file10aptr, pid[i], true);
	}

	for (i = 0; i < num; i++)
	{
		bufMgr->readPage(file10aptr, pid[i], page);
		
		sprintf((char*)&tmpbuf, "test.10 Page %d %7.1f", pid[i], (float)pid[i]);
		if(strncmp(page->getRecord(rid[i]).c_str(), tmpbuf, strlen(tmpbuf)) != 0)
		{
			PRINT_ERROR("ERROR :: CONTENTS DID NOT MATCH");
		}

	}

	// Unpin and dispose pages
	for (i = 0; i < num; i++) {
		bufMgr->disposePage(file10aptr, pid[i]);
	}

	// Try reading pages in file10b that don't exist
	for (i = 0; i < num; i++) {
		try {
			bufMgr->readPage(file10bptr, pid[i], page);
			PRINT_ERROR("ERROR :: Should not be able to read page from file10a here");
		}
		catch (InvalidPageException) {
			
		}
	}

	bufMgr->flushFile(file8ptr);

	std::cout<< "Test 10 passed" << "\n";
}

// Unpin pinned pages and unpin unpinned pages
void test11() {
	for (i = 0; i < num; i++)
	{
		// allocates page and stores the page number in pid[i]		
		bufMgr->allocPage(file11ptr, pid[i], page);
		
		// unpins every page (pages[i] should be dirty)
		bufMgr->unPinPage(file11ptr, pid[i], true);
	}

	for (i = 0; i < num; i++)
	{
		try {
			bufMgr->unPinPage(file11ptr, pid[i], true);
			PRINT_ERROR("ERROR :: Page already unpinned, should have thrown PageNotPinnedException.");
		}
		catch (PageNotPinnedException) {

		}
	}

	// Flush file 1 so we can use it for more tests...
	try
	{
		bufMgr->flushFile(file11ptr);
	}
	catch(PagePinnedException e)
	{
		PRINT_ERROR("ERROR :: In flushFile(). All pages should be been unpinned!");
	}

	std::cout<< "Test 11 passed" << "\n";

}
