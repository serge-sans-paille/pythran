from .method_in_imported_module import aa
# importing another module can produce funny things too
def CC():
    return [aa(h) for h in range(10)]

def DD():
    return [CC for CC in range(10)]
