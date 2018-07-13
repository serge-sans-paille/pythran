# pythran export _brief_loop(float64[:,:], uint8[:,:],
#                            intp[:,:], int[:,:], int[:,:])


def _brief_loop(image, descriptors, keypoints, pos0, pos1):
    for k in range(len(keypoints)):
        kr, kc = keypoints[k]
        for p in range(len(pos0)):
            pr0, pc0 = pos0[p]
            pr1, pc1 = pos1[p]
            descriptors[k, p] = (image[kr + pr0, kc + pc0]
                                 < image[kr + pr1, kc + pc1])
