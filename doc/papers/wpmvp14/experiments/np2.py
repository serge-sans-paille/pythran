#pythran export np2(float [], float[], float [], float [])
import numpy as np
def np2(theta_1, theta_2, phi_1, phi_2):
    temp = np.sin((theta_2-theta_1)/2)**2+np.cos(theta_1)*np.cos(theta_2)*np.sin((phi_2-phi_1)/2)**2
    return 2 * (np.arctan2(np.sqrt(temp),np.sqrt(1-temp)))
