To Create An Executable:

  Type “make plagiarismCatcher”

To Run Executable:

  Type “./plagiarismCatcher” followed by directory path, number of words to detect, and occurences
  For example, if folder of text files are in the same directory, type "./folder_name/" 
  For example, if you want to see about how many same 10 word phrases people had, type "10"
  For example, if you want to see similar text files of 10 word phrases over 100 times, type "100"
  Example -> ./plagiarismCatcher ./sm_doc_set/ 6 200
  
  NOTE: Large dataset may take more time.
        Requires c++11 compatibility. May need to type "module load gcc." 
        For runtime and compatibility, the hash function may have false positives and have lower confidence over larger           dataset.
