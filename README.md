# What it does
Simple code to retrieve :
- Class size
- Class name address
- Class name address pointer
- Class vTable address
- Class vTable address pointer

# How to use
Add classes name from which you want to get the informations here : https://github.com/ApourtArtt/DelphiClassInfo/blob/main/DelphiClassInfo/dllmain.cpp#L12 \
You can print them by `print(ClassSearcher::GetClassInfoFromName("Your class name"));`\
Build it, inject in your target, done.\
Should work only for Delphi 7, would be a surprise if it works for another version.
