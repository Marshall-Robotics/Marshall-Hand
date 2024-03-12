import numpy as np
import cv2
import math






class preprocessdata:
    
    def __init__(self, topology, num_parts):
        self.avg = {"thumb":[0,0,0],
       "index_finger":[0,0,0],
       "middle":[0,0,0],
       "ring":[0,0,0],
       "pinky":[0,0,0]
        }
        self.joints = []
        self.dist_bn_joints = []
        self.topology = topology
        self.num_parts = num_parts
        self.text = "no hand"
        self.num_frames = 4
        self.prev_queue = [self.num_frames] * self.num_frames
        
    # Helper function to calculate angle between three points
#     def calculate_angle(self, p1, p2, p3):
#         a = np.array(p2) - np.array(p1)
#         b = np.array(p2) - np.array(p3)
#         angle = np.arccos(np.clip(np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b)), -1.0, 1.0))
#         return np.degrees(angle)
    def calculate_angle(self, p1, p2, p3):
        a = np.array(p2) - np.array(p1)
        b = np.array(p2) - np.array(p3)
        # Ensure the dot product is divided by non-zero norms, and clip the values to the valid range of -1 to 1
        inner_angle = np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b) + 1e-6)
        angle = np.arccos(np.clip(inner_angle, -1.0, 1.0))
        return np.degrees(angle)


    # Helper function to normalize angles to a range of 0-99
#     def normalize_angle(self, angle, max_angle=180):
#         # Assuming max_angle is the angle for a fully extended finger
#         # This will invert the scale: smaller angles will give higher values
#         return max(0, min(99, (1 - (angle / max_angle)) * 99))


    def normalize_angle(self, angle, max_angle):
        # Assuming a smaller angle indicates a more bent finger
        return max(0, min(99, (max_angle - angle) / max_angle * 99))

#     def calculate_finger_extensions(self, joints):
#         """
#         Calculate the extension for each finger and return normalized values.
#         Assumes joints are ordered from the base of the thumb to the tip, then index, etc.
#         """
#         extensions = []

#         # Finger keypoint indices based on the provided keypoint list
#         finger_keypoints = {
#             'thumb': [1, 2, 3, 4],
#             'index_finger': [5, 6, 7, 8],
#             'middle_finger': [9, 10, 11, 12],
#             'ring_finger': [13, 14, 15, 16],
#             'baby_finger': [17, 18, 19, 20]
#         }

#         # Iterate over each finger
#         for finger, indices in finger_keypoints.items():
#             # Get the keypoints for the base, mid1, mid2, and tip of the finger
#             base, mid1, mid2, tip = [joints[i] for i in indices]

#             # Calculate the angles at the middle and tip joints (ignoring the palm)
#             angle_mid = self.calculate_angle(joints[0], base, mid1)
#             angle_tip = self.calculate_angle(base, mid2, tip)

#             # We can refine how we calculate the "extension" based on these two angles
#             # For simplicity, we'll average them
#             avg_angle = (angle_mid + angle_tip) / 2
#             extension = self.normalize_angle(avg_angle)

#             extensions.append(extension)

#         return extensions

    def calculate_finger_extensions(self, joints):
        
        global avg
        
        """
        Calculate the extension for each finger and return normalized values.
        Assumes joints are ordered from the base of the thumb to the tip, then index, etc.
        """
        
        # Check if all joints are [0, 0] which means no hand is detected
        if all(x == [0, 0] for x in joints):
            return [99, 99, 99, 99, 99]  # All fingers fully extended

        
        extensions = []
        # The angle considered fully extended for each finger
        max_angles = {'thumb': 45, 'index_finger': 180, 'middle_finger': 180, 'ring_finger': 180, 'baby_finger': 180}

        # Finger keypoint indices based on the provided keypoint list
        finger_keypoints = {
            'thumb': [0, 1, 2],
            'index_finger': [0, 5, 6],
            'middle_finger': [0, 9, 10],
            'ring_finger': [0, 13, 14],
            'baby_finger': [0, 17, 18]
        }

        # Iterate over each finger
        key = 0 
        
        for finger, indices in finger_keypoints.items():
            
            palm, base, mid = [joints[i] for i in indices]
            angle = self.calculate_angle(palm, base, mid)
            extension = self.normalize_angle(angle, max_angles[finger])
            
            extension_result = (extension + self.avg[i][1][2] + self.avg[i][1][1] + self.avg[i][1][0])/4
            
            #extension_result = (extension + sum(for y in avg[i][1]))/4
            
            self.avg[key][1][2] = self.avg[key][1][1]
            self.avg[key][1][1] = self.avg[key][1][0]
            self.avg[key][1][0] = extension
            
            
            if 0<extension_result<20:
                extension_result = 0
            elif 20<extension_result<40:
                extension_result = 1
            elif 40<extension_result<60:
                extension_result = 2
            elif 60<extension_result<80:
                extension_result = 3
            elif 80<extension_result<100:
                extension_result = 4
                
            
            extensions.append(extension_result)
            
            i = i+1
        
        return extensions


    def print_finger_extensions(self, image, extensions, i_frame):
        """
        Print the finger extension values on the image.
        """
        font = cv2.FONT_HERSHEY_SIMPLEX 
        font_scale = 0.5
        color = (255, 255, 255)  # White color
        thickness = 2
        line_type = cv2.LINE_AA
        
        x, y = 10, 60
        
        #print i 
        cv2.putText(image, f"{i_frame}", (x, y), font, font_scale, color, thickness, line_type)

        # Coordinates to start printing the finger extension values
        x, y = 10, 80

        # Names of fingers
        finger_names = ['T', 'I', 'M', 'R', 'P']

        # Print each finger's extension value
        for i, value in enumerate(extensions):
            text = f'{finger_names[i]}: {value:.2f}'
            cv2.putText(image, text, (x, y + i*20), font, font_scale, color, thickness, line_type)

        return image

    

    
    
    
    
    
    
    def svm_accuracy(self, test_predicted, labels_test):
        """"
        This method calculates the accuracy of the model 
        Input: test_predicted - predicted test classes
               labels_test
        Output: accuracy - of the model 
        """
        predicted = []
        for i in range(len(labels_test)):
            if labels_test[i]==test_predicted[i]:
                predicted.append(0)
            else:
                predicted.append(1)
        accuracy = 1 - sum(predicted)/len(labels_test)
        return accuracy 
    def trainsvm(self, clf, train_data, test_data, labels_train, labels_test):
        """
        This method trains the different gestures 
        Input: clf - Sk-learn model pipeline to train, You can choose an SVM, linear regression, etc
                train_data - preprocessed training image data -in this case the distance between the joints
                test_data - preprocessed testing image data -in this case the distance between the joints
                labels_train - labels for training images 
                labels_test - labels for testing images 
        Output: trained model, predicted_test_classes
        """
        clf.fit(train_data,labels_train)
        predicted_test = clf.predict(test_data)
        return clf, predicted_test   
    #def loadsvmweights():
    
    def joints_inference(self, image, counts, objects, peaks): 
        """
        This method returns predicted joints from an image/frame
        Input: image, counts, objects, peaks
        Output: predicted joints
        """
        joints_t = []
        height = image.shape[0]
        width = image.shape[1]
        K = self.topology.shape[0]
        count = int(counts[0])
        for i in range(count):
            obj = objects[0][i]
            C = obj.shape[0]
            for j in range(C):
                k = int(obj[j])
                picked_peaks = peaks[0][j][k]
                joints_t.append([round(float(picked_peaks[1]) * width), round(float(picked_peaks[0]) * height)])
        joints_pt = joints_t[:self.num_parts]  
        rest_of_joints_t = joints_t[self.num_parts:]
        
        #when it does not predict a particular joint in the same association it will try to find it in a different association 
        for i in range(len(rest_of_joints_t)):
            l = i%self.num_parts
            if joints_pt[l] == [0,0]:
                joints_pt[l] = rest_of_joints_t[i]
                
        #if nothing is predicted 
        if count == 0:
            joints_pt = [[0,0]]*self.num_parts
        return joints_pt
    
    def find_distance(self, joints):
        """
        This method finds the distance between each joints 
        Input: a list that contains the [x,y] positions of the 21 joints 
        Output: a list that contains the distance between the joints 
        """
        joints_features = []
        for i in joints:
            for j in joints:
                dist_between_i_j = math.sqrt((i[0]-j[0])**2+(i[1]-j[1])**2)
                joints_features.append(dist_between_i_j)
        return joints_features
    
    def print_label(self, image, gesture_joints, gesture_type):
        """
        This method prints the gesture class detected. 
        Example. Incase of the cursor control application it shows if your gesture is a click or other type of gesture
        
        """
        font = cv2.FONT_HERSHEY_SIMPLEX 
        color = (255, 0, 0) 
        org = (50, 50)
        thickness = 2
        fontScale = 0.5
        no_frames = 4
        if self.prev_queue == [1]* self.num_frames:
            self.text = gesture_type[0]
        elif self.prev_queue == [2]* self.num_frames:
            self.text = gesture_type[1]
        elif self.prev_queue == [3]* self.num_frames:
            self.text = gesture_type[2]
        elif self.prev_queue == [4]* self.num_frames:
            self.text = gesture_type[3]
        elif self.prev_queue == [5]* self.num_frames:
            self.text = gesture_type[4]
        elif self.prev_queue == [6]* self.num_frames:
            self.text = gesture_type[5]
        elif self.prev_queue == [7]*self.num_frames:
            self.text = gesture_type[6]
        image = cv2.putText(image, self.text, org, font,  
                       fontScale, color, thickness, cv2.LINE_AA) 
        return image
