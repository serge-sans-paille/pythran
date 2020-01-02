#pythran export average_position(str:(float,float) dict, str:(float,float) dict)
#runas d = {"e":(1.,2.) } ; e = {"d":(2.,1.) } ; average_position(e,d)

def average_position(pos1,pos2):
	pos_avg={}
	for k in pos1:
		if k in pos2:
			pos_avg[k]=((pos1[k][0]+pos2[k][0])/2,(pos1[k][1]+pos2[k][1])/2)
		else:
			pos_avg[k]=pos1[k]
	for k in pos2:
		if k in pos1:
			if k not in pos_avg:
				pos_avg[k]=((pos1[k][0]+pos2[k][0])/2,(pos1[k][1]+pos2[k][1])/2)
		else:
			pos_avg[k]=pos2[k]
	return pos_avg
