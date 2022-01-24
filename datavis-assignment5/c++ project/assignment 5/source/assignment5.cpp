//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2017, 2018 CGV TU Dresden - All Rights Reserved
//

#include <vtkAutoInit.h>
// Needed for general rendering
VTK_MODULE_INIT(vtkRenderingOpenGL2);
// Needed for interactive controls
VTK_MODULE_INIT(vtkInteractionStyle);
// Guess what that is needed for
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
// Needed for the text on the slider
VTK_MODULE_INIT(vtkRenderingFreeType);

#include "vtkhelper.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <vtkXMLImageDataReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkSmartVolumeMapper.h>

#include <vtkMarchingCubes.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>

#include <vtkSliderRepresentation2D.h>
#include <vtkSliderWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkInteractorStyleTrackballCamera.h>

class IsoSliderCallback : public vtkCommand {
private:
	IsoSliderCallback() {}

public:
	vtkSmartPointer<vtkMarchingCubes> isoSurface;

	static IsoSliderCallback *New() { return new IsoSliderCallback; }

	void SetData( vtkSmartPointer<vtkMarchingCubes> isoSurface ) { this->isoSurface = isoSurface; }

	virtual void Execute( vtkObject *caller, unsigned long eventId, void *callData ) {
		// Get our slider widget back
		vtkSliderWidget *slider = static_cast<vtkSliderWidget*>(caller);

		// Get the value
		double value = static_cast<vtkSliderRepresentation*>(slider->GetRepresentation())->GetValue();

		// Set new Iso value
		isoSurface->SetValue( 0, value );
		isoSurface->Update();
	}
};


void doRenderingAndInteraction(vtkSmartPointer<vtkRenderWindow> window)
{
	// create interactor and connect a window
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);
	// set an interaction style
	interactor->SetInteractorStyle(vtkInteractorStyleTrackballCamera::New());

	// execute render/interaction loop
	interactor->Initialize();
	interactor->Start();

	// close the window when finished
	window->Finalize();
}

void doRenderingAndInteraction(vtkSmartPointer<vtkRenderWindowInteractor> interactor, vtkSmartPointer<vtkRenderWindow> window)
{
	// execute render/interaction loop
	interactor->Initialize();
	interactor->Start();

	// close the window when finished
	window->Finalize();
}


int main()
{
	vtkSmartPointer<vtkXMLImageDataReader> source = vtkSmartPointer<vtkXMLImageDataReader>::New();
	source->SetFileName("../data/headsq-half.vti");
	source->Update();

	// Task 5.2

	// visualize volume directly:
	// * create a vtkSmartVolumeMapper that gets its input from the source
	vtkSmartPointer<vtkSmartVolumeMapper> volMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	volMapper->SetInputConnection(source->GetOutputPort());

	// * enable GPU rendering and set the appropriate volume blending
	volMapper->SetRequestedRenderModeToGPU();
	volMapper->SetBlendModeToComposite();

	// * create an opacity transfer function as vtkPiecewiseFunction and add density-opacity pairs
	vtkSmartPointer<vtkPiecewiseFunction> opacityFunc = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacityFunc->AddPoint(-3024, 0, 0.5, 0.0);
	opacityFunc->AddPoint(-16, 0, .49, .61);
	opacityFunc->AddPoint(3071, .71, 0.5, 0.0);

	// * create a color transfer function as vtkColorTransferFunction and add density-color pairs
	vtkSmartPointer<vtkColorTransferFunction> colorFunc = vtkSmartPointer<vtkColorTransferFunction>::New();
	colorFunc->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	colorFunc->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
	colorFunc->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
	colorFunc->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

	// * create a vtkVolumeProperty object, set the opacity and color function and set the 
	//   interpolation type to linear. Turn shading on
	vtkSmartPointer<vtkVolumeProperty> volProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volProperty->SetScalarOpacity(opacityFunc);
	volProperty->SetColor(colorFunc);
	volProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);
	volProperty->ShadeOn();
	
	// * create the actor as a vtkVolume object and assign the previously created volume mapper and property object
	vtkSmartPointer<vtkVolume> volActor = vtkSmartPointer<vtkVolume>::New();
	volActor->SetProperty(volProperty);
	volActor->SetMapper(volMapper);
	
	// * create a vtkRenderer and a vtkRenderWindow. (Note that you cannot use the method createRenderWindowFromMapper 
	//   since it does not create a vtkVolume actor.)
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->GradientBackgroundOn();
	renderer->SetBackground(0, 0, 0);
	renderer->SetBackground2(0.2, 0.2, 0.2);
	renderer->AddVolume(volActor);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(renderer);
	window->SetSize(1000, 600); // set window size
	
	// * you can create interactor and display as usual via doRenderingAndInteraction(window) to test your code to this point.
	// (delete the line when you're done)
	// doRenderingAndInteraction(window);



	
	// visualize volume via isosurfaces:
	// * generate polygon data from the volume dataset by using a vtkMarchingCubes filter
	vtkSmartPointer<vtkMarchingCubes> skinExtractor = vtkSmartPointer<vtkMarchingCubes>::New();
	skinExtractor->SetInputConnection(source->GetOutputPort());

	// * set number of contours to one, set scalar value of that contour to something meaningful
	// An isosurface, or contour value of 500 is known to correspond to the skin of the patient.
	skinExtractor->SetValue(0, 500);

	// * manually update the Marching Cubes filter aftwerwards via Update() method to apply the contour value
	skinExtractor->Update();

	// * create vtkDataSetMapper and set input connection, don't use scalars for coloring (set scalar visibility to false)
	vtkSmartPointer<vtkDataSetMapper> skinMapper = vtkSmartPointer<vtkDataSetMapper>::New();
	skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
	skinMapper->ScalarVisibilityOff();

	// * create vtkActor and set mapper as input
	vtkSmartPointer<vtkActor> skinActor = vtkSmartPointer<vtkActor>::New();
	skinActor->SetMapper(skinMapper);

	// * assign actor to existing renderer
	renderer->AddActor(skinActor);




	// * create a slider as a slider 2d representation
	vtkSmartPointer<vtkSliderRepresentation2D> sliderRep = vtkSmartPointer<vtkSliderRepresentation2D>::New();

	// * set the minimum and maximum values to correspond to the dataset
	sliderRep->SetMinimumValue(0.0);
	sliderRep->SetMaximumValue(4100.0);
	sliderRep->SetValue(100.0);
	
	// set a fixed point co-ordinate for slider
	sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep->GetPoint1Coordinate()->SetValue(100, 100);
	sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep->GetPoint2Coordinate()->SetValue(300, 100);
	
	// * show a slider title
	sliderRep->SetTitleText("Iso Value");

	// * show the current slider value above the slider with one digit behind the decimal point (setLabelFormat)
	sliderRep->SetLabelFormat("%0.1f");



	
	// * you need to assign an interactor to the slider in order to use it: 
	// * create a vtkRenderWindowInteractor and assign a rendering window 
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);
	
	// * create a new vtkSliderWidget and assign the previous interactor and representation to it
	vtkSmartPointer<vtkSliderWidget> sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
	sliderWidget->SetInteractor(interactor);
	sliderWidget->SetRepresentation(sliderRep);

	// * use SetAnimationModeToAnimate() and EnabledOn()
	sliderWidget->SetAnimationModeToAnimate();
	sliderWidget->EnabledOn();




	// * invoke the callback code:
	// * create an IsoSlider Callback
	vtkSmartPointer<IsoSliderCallback> callback = vtkSmartPointer<IsoSliderCallback>::New();

	// * assign the Marching Cubes data
	callback->isoSurface = skinExtractor;
	
	// * assign the callback object to the slider via AddObserver(vtkCommand::InteracationEvent, ptrToCallback);
	sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	// * finally you can then use the version of doRenderingAndInteraction that accepts an interactor object.
	doRenderingAndInteraction(interactor, window);

	return 0;
}
